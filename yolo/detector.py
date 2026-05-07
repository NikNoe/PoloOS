#!/usr/bin/env python3
"""
PoloOS — detector.py
YOLO + OpenCV → détection objets → envoi UDP vers Raylib
Usage : python3 yolo/detector.py --video assets/circulation-video/video.mp4
"""

import cv2
import argparse
import time
import math
import numpy as np
from ultralytics import YOLO
from socket_sender import SocketSender

# ── Classes YOLO à détecter ───────────────────────────────────────────────────
TRACKED_CLASSES = {
    0:  "pedestrian",
    1:  "bicycle",
    2:  "car",
    3:  "motorcycle",
    5:  "bus",
    7:  "truck",
    9:  "traffic_light",
    11: "stop_sign",
    13: "bench",
}

# ── Paramètres caméra (estimations dashcam) ───────────────────────────────────
CAMERA_HEIGHT_M   = 1.2    # hauteur caméra au-dessus du sol (m)
CAMERA_FOV_DEG    = 60.0   # champ de vision horizontal
CAMERA_PITCH_DEG  = -5.0   # inclinaison vers le bas


def estimate_distance(bbox_h: float, frame_h: float, obj_class: str) -> float:
    """
    Estime la distance en mètres depuis la hauteur de la bounding box.
    Basé sur la taille réelle connue des objets.
    """
    real_heights = {
        "car":        1.5,
        "truck":      3.5,
        "bus":        3.0,
        "pedestrian": 1.75,
        "bicycle":    1.1,
        "motorcycle": 1.2,
        "traffic_light": 0.6,
        "stop_sign":  0.75,
    }
    real_h = real_heights.get(obj_class, 1.5)

    # focal length estimée
    focal = frame_h / (2.0 * math.tan(math.radians(CAMERA_FOV_DEG / 2.0)))

    if bbox_h < 1:
        return 999.0

    distance = (real_h * focal) / bbox_h
    return round(distance, 2)


def bbox_to_world(cx_norm: float, distance: float,
                  frame_w: float) -> tuple[float, float]:
    """
    Convertit position 2D normalisée + distance → coordonnées monde (x, z).
    x = latéral, z = profondeur (devant la voiture)
    """
    # Angle horizontal depuis le centre
    angle_h = (cx_norm - 0.5) * math.radians(CAMERA_FOV_DEG)
    x = distance * math.sin(angle_h)
    z = distance * math.cos(angle_h)
    return round(x, 2), round(z, 2)

class EgoMotion:
    """Estime vitesse + rotation depuis optical flow entre deux frames."""

    def __init__(self):
        self.prev_gray  = None
        self.prev_pts   = None
        self.fps        = 30.0

    def update(self, frame: np.ndarray, fps: float) -> dict:
        self.fps   = fps
        gray       = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        result     = {"speed": 0.0, "heading_delta": 0.0}

        if self.prev_gray is None:
            self.prev_gray = gray
            return result

        # Détecte points d'intérêt sur frame précédente
        pts = cv2.goodFeaturesToTrack(
            self.prev_gray,
            maxCorners=120,
            qualityLevel=0.01,
            minDistance=10,
            blockSize=7
        )

        if pts is None or len(pts) < 8:
            self.prev_gray = gray
            return result

        # Suit les points sur la frame courante
        next_pts, status, _ = cv2.calcOpticalFlowPyrLK(
            self.prev_gray, gray, pts, None,
            winSize=(21, 21), maxLevel=3
        )

        # Garde uniquement les points bien trackés
        good_prev = pts[status == 1]
        good_next = next_pts[status == 1]

        if len(good_prev) < 6:
            self.prev_gray = gray
            return result

        h, w = gray.shape
        cx, cy = w / 2.0, h / 2.0

        # Mouvement moyen des points
        dx = float(np.median(good_next[:, 0] - good_prev[:, 0]))
        dy = float(np.median(good_next[:, 1] - good_prev[:, 1]))

        # Vitesse estimée depuis le flux optique vertical
        # dy > 0 = route s'éloigne = on avance
        pixel_per_meter = h / 20.0   # estimation grossière
        speed_mps = max(0.0, -dy) / pixel_per_meter * fps
        speed_kmh = round(speed_mps * 3.6, 1)

        # Rotation estimée depuis le flux horizontal
        heading_delta = round(-dx / w * 15.0, 2)  # degrés/frame

        self.prev_gray = gray
        return {
            "speed":         speed_kmh,
            "heading_delta": heading_delta
        }


def run(video_path: str, model_size: str, conf: float,
        host: str, port: int, show: bool, skip: int):

    print(f"[PoloOS] Chargement YOLO {model_size}...")
    model = YOLO(f"yolov{model_size}.pt")

    print(f"[PoloOS] Ouverture vidéo : {video_path}")
    cap = cv2.VideoCapture(video_path)
    ego_motion = EgoMotion()
    if not cap.isOpened():
        print(f"[ERREUR] Impossible d'ouvrir : {video_path}")
        return

    fps        = cap.get(cv2.CAP_PROP_FPS) or 30.0
    frame_w    = cap.get(cv2.CAP_PROP_FRAME_WIDTH)
    frame_h    = cap.get(cv2.CAP_PROP_FRAME_HEIGHT)
    total      = int(cap.get(cv2.CAP_PROP_FRAME_COUNT))

    print(f"[PoloOS] Vidéo : {frame_w}x{frame_h} @ {fps}fps — {total} frames")
    print(f"[PoloOS] Envoi UDP → {host}:{port}")

    sender    = SocketSender(host, port)
    frame_idx = 0
    t_start   = time.time()

    while cap.isOpened():
        ret, frame = cap.read()
        if not ret:
            print("[PoloOS] Fin de vidéo")
            break

        frame_idx += 1

        # Skip frames pour alléger le CPU
        if frame_idx % (skip + 1) != 0:
            continue

        timestamp = frame_idx / fps

        # ── Détection YOLO ────────────────────────────────────────────────────
        results = model(frame, conf=conf, verbose=False)[0]

        ego = ego_motion.update(frame, fps)

        objects = []
        for box in results.boxes:
            cls_id = int(box.cls[0])
            if cls_id not in TRACKED_CLASSES:
                continue

            cls_name   = TRACKED_CLASSES[cls_id]
            confidence = float(box.conf[0])

            # Bounding box
            x1, y1, x2, y2 = box.xyxy[0].tolist()
            bbox_w = x2 - x1
            bbox_h = y2 - y1
            cx     = (x1 + x2) / 2.0
            cy     = (y1 + y2) / 2.0

            # Normalisation
            cx_norm = cx / frame_w
            cy_norm = cy / frame_h

            # Estimation distance + position monde
            distance      = estimate_distance(bbox_h, frame_h, cls_name)
            world_x, world_z = bbox_to_world(cx_norm, distance, frame_w)

            # Heading estimé (simplifié — sera amélioré avec tracking)
            heading = 180.0 if world_z > 0 else 0.0

            obj = {
                "class":      cls_name,
                "x":          world_x,
                "z":          world_z,
                "heading":    heading,
                "confidence": round(confidence, 3),
                "distance":   distance,
    
            }
            objects.append(obj)

        # ── Envoi UDP ─────────────────────────────────────────────────────────
        sender.send(frame_idx, timestamp, objects, ego)

        # ── Affichage optionnel ───────────────────────────────────────────────
        if show:
            annotated = results.plot()

            # Overlay infos
            elapsed = time.time() - t_start
            real_fps = frame_idx / elapsed if elapsed > 0 else 0
            cv2.putText(annotated,
                        f"Frame {frame_idx}/{total} | "
                        f"{real_fps:.1f} fps | "
                        f"{len(objects)} objets",
                        (10, 30), cv2.FONT_HERSHEY_SIMPLEX,
                        0.7, (0, 255, 0), 2)

            cv2.imshow("PoloOS — YOLO Detector", annotated)
            if cv2.waitKey(1) & 0xFF == ord('q'):
                break

        # ── Throttle pour coller au FPS vidéo ────────────────────────────────
        elapsed   = time.time() - t_start
        expected  = frame_idx / fps
        sleep_for = expected - elapsed
        if sleep_for > 0:
            time.sleep(sleep_for)

    cap.release()
    if show:
        cv2.destroyAllWindows()
    sender.close()
    print("[PoloOS] Détection terminée")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="PoloOS YOLO Detector")
    parser.add_argument("--video",  default="0",
                        help="Chemin vidéo ou index caméra (défaut: 0)")
    parser.add_argument("--model",  default="8n",
                        help="Taille modèle YOLO : 8n, 8s, 8m (défaut: 8n)")
    parser.add_argument("--conf",   type=float, default=0.45,
                        help="Seuil confiance (défaut: 0.45)")
    parser.add_argument("--host",   default="127.0.0.1",
                        help="IP Raylib (défaut: localhost)")
    parser.add_argument("--port",   type=int, default=5005,
                        help="Port UDP (défaut: 5005)")
    parser.add_argument("--show",   action="store_true",
                        help="Affiche la fenêtre OpenCV")
    parser.add_argument("--skip",   type=int, default=1,
                        help="Skip N frames entre chaque détection (défaut: 1)")
    args = parser.parse_args()

    run(
        video_path = args.video,
        model_size = args.model,
        conf       = args.conf,
        host       = args.host,
        port       = args.port,
        show       = args.show,
        skip       = args.skip,
    )