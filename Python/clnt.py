# 캡쳐화면 TCP/IP 통신
#
# -*- coding: utf-8 -*-

import socket
import time
import os

import mss
import cv2
import numpy

UDP_IP = "localhost"
UDP_PORT = 30000

#sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

with mss.mss() as sct:
    monitor = {"top" : 0, "left" : 0, "width" : 1280, "height" : 800}
    img = numpy.array(sct.grab(monitor))

data = numpy.array(img, dtype = 'f8')

print(type(data))
print(len(data))

#sock.sendto(data, (UDP_IP, UDP_PORT))
