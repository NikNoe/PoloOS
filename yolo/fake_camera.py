#!/usr/bin/env python3
"""
PoloOS — fake_camera.py
Simule une caméra depuis un fichier vidéo.
Utile pour tester sans caméra physique.
"""

import cv2
import time


class FakeCamera:
    def __init__(self, video_path: str, loop: bool = True):
        self.path  = video_path
        self.loop  = loop
        self.cap   = cv2.VideoCapture(video_path)
        self.fps   = self.cap.get(cv2.CAP_PROP_FPS) or 30.0
        self.delay = 1.0 / self.fps

        if not self.cap.isOpened():
            raise RuntimeError(f"Impossible d'ouvrir : {video_path}")

        print(f"[FakeCamera] {video_path}")
        print(f"  FPS: {self.fps} | "
              f"Frames: {int(self.cap.get(cv2.CAP_PROP_FRAME_COUNT))}")

    def read(self):
        ret, frame = self.cap.read()
        if not ret and self.loop:
            self.cap.set(cv2.CAP_PROP_POS_FRAMES, 0)
            ret, frame = self.cap.read()
        return ret, frame

    def release(self):
        self.cap.release()