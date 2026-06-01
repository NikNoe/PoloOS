#!/usr/bin/env python3
"""
PoloOS -- detector.py
YOLO + OpenCV + EgoMotion -> UDP to Raylib
"""

import cv2
import argparse
import time
import math
import numpy as np
from ultralytics import YOLO
from socket_sender import SocketSender

TRACKED_CLASSES = {
    0:  "pedestrian",
    1:  "bicycle",
    2:  "car",
    3:  "motorcycle",
    5:  "bus",
    7:  "truck",
    9:  "traffic_light",
    11: "stop_sign",
}

CAMERA_FOV_DEG = 60.0


def estimate_distance(bbox_h: float, frame_h: float, obj_class: str) -> float:
    real_heights = {
        "car": 1.5, "truck": 3.5, "bus": 3.0,
        "pedestrian": 1.75, "bicycle": 1.1,
        "motorcycle": 1.2, "traffic_light": 0.6, "stop_sign": 0.75,
    }
    real_h = real_heights.get(obj_class, 1.5)
    focal  = frame_h / (2.0 * math.tan(math.radians(CAMERA_FOV_DEG / 2.0)))
    if bbox_h < 1:
        return 999.0
    return round((real_h * focal) / bbox_h, 2)


def bbox_to_world(cx_norm: float, distance: float, frame_w: float):
    angle_h = (cx_norm - 0.5) * math.radians(CAMERA_FOV_DEG)
    x = distance * math.sin(angle_h)
    z = distance * math.cos(angle_h)
    return round(x, 2), round(z, 2)


class EgoMotion:
    def __init__(self):
        self.prev_gray = None

    def update(self, frame: np.ndarray, fps: float) -> dict:
        gray   = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        result = {"speed": 0.0, "heading_delta": 0.0}

        if self.prev_gray is None:
            self.prev_gray = gray
            return result

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

        next_pts, status, _ = cv2.calcOpticalFlowPyrLK(
            self.prev_gray, gray, pts, None,
            winSize=(21, 21), maxLevel=3
        )

        good_prev = pts[status == 1]
        good_next = next_pts[status == 1]

        if len(good_prev) < 6:
            self.prev_gray = gray
            return result

        h_img, w_img = gray.shape

        dx = float(np.median(good_next[:, 0] - good_prev[:, 0]))
        dy = float(np.median(good_next[:, 1] - good_prev[:, 1]))

        # Vitesse depuis flux vertical
        pixel_per_meter = h_img / 20.0
        speed_mps = max(0.0, -dy) / pixel_per_meter * fps
        speed_kmh = round(speed_mps * 3.6, 1)

        # Rotation depuis points bas de l'image
        bottom_mask = good_prev[:, 1] > h_img * 0.5
        if bottom_mask.sum() > 4:
            bottom_dx     = float(np.median(good_next[bottom_mask, 0] - good_prev[bottom_mask, 0]))
            heading_delta = round(-bottom_dx / w_img * 25.0, 2)
        else:
            heading_delta = round(-dx / w_img * 15.0, 2)

        self.prev_gray = gray
        return {"speed": speed_kmh, "heading_delta": heading_delta}


def run(video_path, model_size, conf, host, port, show, skip):
    print(f"[PoloOS] Chargement YOLO {model_size}...")
    model = YOLO(f"yolov{model_size}.pt")

    print(f"[PoloOS] Opening video: {video_path}")
    cap = cv2.VideoCapture(video_path)
    if not cap.isOpened():
        print(f"[ERREUR] Impossible d'ouvrir : {video_path}")
        return

    fps     = cap.get(cv2.CAP_PROP_FPS) or 30.0
    frame_w = cap.get(cv2.CAP_PROP_FRAME_WIDTH)
    frame_h = cap.get(cv2.CAP_PROP_FRAME_HEIGHT)
    total   = int(cap.get(cv2.CAP_PROP_FRAME_COUNT))

    print(f"[PoloOS] {frame_w}x{frame_h} @ {fps}fps -- {total} frames")

    sender     = SocketSender(host, port)
    ego_motion = EgoMotion()
    frame_idx  = 0
    t_start    = time.time()

    while cap.isOpened():
        ret, frame = cap.read()
        if not ret:
            break

        frame_idx += 1
        if frame_idx % (skip + 1) != 0:
            continue

        timestamp = frame_idx / fps

        # Ego motion
        ego = ego_motion.update(frame, fps)

        # YOLO detection
        results = model.track(frame, conf=conf, iou=0.45, 
                      persist=True, verbose=False)[0]
        objects = []
        for box in results.boxes:
            cls_id = int(box.cls[0])
            if cls_id not in TRACKED_CLASSES:
                continue

            cls_name   = TRACKED_CLASSES[cls_id]
            confidence = float(box.conf[0])
            x1, y1, x2, y2 = box.xyxy[0].tolist()
            bbox_h  = y2 - y1
            cx_norm = ((x1 + x2) / 2.0) / frame_w

            distance          = estimate_distance(bbox_h, frame_h, cls_name)
            # In the objects loop, after estimate_distance:
            if distance < 3.0 or distance > 80.0:
                continue
            world_x, world_z  = bbox_to_world(cx_norm, distance, frame_w)

            objects.append({
                "class":      cls_name,
                "x":          world_x,
                "z":          world_z,
                "heading":    180.0,
                "confidence": round(confidence, 3),
                "distance":   distance,
            })

        sender.send(frame_idx, timestamp, objects, ego)

        for box in results.boxes:
            cls_id = int(box.cls[0])
            if cls_id not in TRACKED_CLASSES:
                continue

            # Unique tracker ID -- None if not yet assigned
            track_id = int(box.id[0]) if box.id is not None else -1
            if track_id == -1:
                continue  # skip detections without a stable ID

            cls_name   = TRACKED_CLASSES[cls_id]
            confidence = float(box.conf[0])
            x1, y1, x2, y2 = box.xyxy[0].tolist()
            bbox_h  = y2 - y1
            cx_norm = ((x1 + x2) / 2.0) / frame_w

            if bbox_h < 20:  # trop petit = trop loin ou bruit
                continue

            distance         = estimate_distance(bbox_h, frame_h, cls_name)
            if distance < 3.0 or distance > 60.0:
                continue

            world_x, world_z = bbox_to_world(cx_norm, distance, frame_w)

            objects.append({
                "class":      cls_name,
                "id":         track_id,    # <- stable tracking ID
                "x":          world_x,
                "z":          world_z,
                "heading":    180.0,
                "confidence": round(confidence, 3),
                "distance":   distance,
            })

        if show:
            annotated = results.plot()
            cv2.putText(annotated,
                        f"Frame {frame_idx}/{total} | spd:{ego['speed']}km/h | {len(objects)} obj",
                        (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 255, 0), 2)
            cv2.imshow("PoloOS -- YOLO", annotated)
            if cv2.waitKey(1) & 0xFF == ord('q'):
                break

        # Precise frame throttle
        target_time = frame_idx / fps
        elapsed     = time.time() - t_start
        sleep_for   = target_time - elapsed
        if sleep_for > 0.005:
            time.sleep(sleep_for)

    cap.release()
    if show:
        cv2.destroyAllWindows()
    sender.close()
    print("[PoloOS] Done")


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--video",  default="0")
    parser.add_argument("--model",  default="8n")
    parser.add_argument("--conf",   type=float, default=0.65)
    parser.add_argument("--host",   default="127.0.0.1")
    parser.add_argument("--port",   type=int,   default=5005)
    parser.add_argument("--show",   action="store_true")
    parser.add_argument("--skip",   type=int,   default=1)
    args = parser.parse_args()

    run(args.video, args.model, args.conf,
        args.host, args.port, args.show, args.skip)
