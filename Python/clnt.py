# 캡쳐화면 TCP/IP 통신
#
# -*- coding: utf-8 -*-

import socket
import time

import mss
import cv2
import numpy

TCP_IP = "localhost"
TCP_PORT = 30000

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((TCP_IP, TCP_PORT))

with mss.mss() as sct:
    mon = sct.monitors[2]
    monitor = {"top" : mon["top"] + 0, "left" : mon["left"] + 0, "width" : 1280, "height" : 800, "mon" : 2}

    img = numpy.array(sct.grab(monitor))

    encode_param = [int(cv2.IMWRITE_JPEG_QUALITY), 90]
    result, imgencode = cv2.imencode('.jpg', img, encode_param)
    data = numpy.array(imgencode)
    stringData = data.tostring()

    s.send(str(len(stringData)).ljust(16))
    s.send(stringData)
    s.close()
    
    decimg = cv2.imdecode(data, 1)
    cv2.imshow('Client', decimg)
    cv2.waitKey(0)
    cv2.destroyAllWindows() 