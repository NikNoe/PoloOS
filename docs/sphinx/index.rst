PoloOS — YOLO Pipeline
======================

Python pipeline that reads dashcam video frames, detects objects with YOLOv8,
estimates their 3D world position, and streams the results to the Raylib C++
engine over UDP (port 5005).

.. code-block:: text

   Dashcam / video file
         │
         ▼
   detector.py  ──►  EgoMotion (optical flow)
         │
         ▼  UDP JSON  (port 5005)
   SceneReceiver.cpp  ──►  TrafficAgent[]  ──►  Raylib render

.. toctree::
   :maxdepth: 2
   :caption: Modules

   modules/detector
   modules/socket_sender
   modules/fake_camera

.. toctree::
   :maxdepth: 1
   :caption: Reference

   genindex

----

JSON packet format
------------------

Every UDP datagram sent by :mod:`socket_sender` has the following structure:

.. code-block:: json

   {
     "seq":       42,
     "frame":     1042,
     "timestamp": 34.7,
     "ego":       { "speed": 12.5, "heading_delta": -0.3 },
     "objects": [
       {
         "class":      "car",
         "id":         7,
         "x":          12.3,
         "z":          45.1,
         "heading":    180.0,
         "confidence": 0.92,
         "distance":   14.5
       }
     ]
   }

.. rubric:: Field descriptions

``seq``
   Monotonically increasing packet counter.

``frame``
   Source video frame index.

``timestamp``
   Frame time in seconds (``frame / fps``).

``ego.speed``
   Ego-vehicle speed in km/h estimated from vertical optical flow.

``ego.heading_delta``
   Heading change in degrees estimated from horizontal optical flow.

``objects[].id``
   YOLOv8 tracker ID — stable across frames for the same physical object.

``objects[].x`` / ``objects[].z``
   Estimated world-space position relative to the camera (metres).
