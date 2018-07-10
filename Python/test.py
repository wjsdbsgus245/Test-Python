# 캡쳐화면 UDP/IP 통신
#
# -*- coding: utf-8 -*-

import socket
import time

import mss
import cv2
import numpy as np

UDP_IP = "localhost"
UDP_PORT = 30000

with mss.mss() as sct:
    monitor = {"top" : 0, "left" : 0, "width" : 1280, "height" : 800}

    img = np.array(sct.grab(monitor))

    encode_param = [int(cv2.IMWRITE_JPEG_QUALITY), 90]
    result, imgencode = cv2.imencode('.png', img, encode_param)
    data = np.array(imgencode)
    stringData = data.tostring()
    
    print(img.shape)

