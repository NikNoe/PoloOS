#!/usr/bin/env python3
"""
PoloOS — socket_sender.py
Envoi UDP JSON vers Raylib SceneReceiver
"""

import socket
import json
import time
from typing import List, Dict


class SocketSender:
    def __init__(self, host: str = "127.0.0.1", port: int = 5005):
        self.host    = host
        self.port    = port
        self.sock    = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.seq     = 0
        print(f"[SocketSender] UDP → {host}:{port}")

    def send(self, frame: int, timestamp: float,
             objects: List[Dict]) -> bool:
        self.seq += 1
        payload = {
            "seq":       self.seq,
            "frame":     frame,
            "timestamp": round(timestamp, 3),
            "objects":   objects,
        }
        try:
            data = json.dumps(payload).encode("utf-8")
            self.sock.sendto(data, (self.host, self.port))
            return True
        except Exception as e:
            print(f"[SocketSender] Erreur envoi : {e}")
            return False

    def close(self):
        self.sock.close()
        print("[SocketSender] Socket fermé")