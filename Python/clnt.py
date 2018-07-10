# 캡쳐화면 TCP/IP 통신
#
# -*- coding: utf-8 -*-

# 화면 크기 지정
import pygame
pygame.init()
infos = pygame.display.Info()

import socket
import mss
import cv2
import numpy as np

TCP_IP = "192.168.100.1"
TCP_PORT = 30000

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

with mss.mss() as sct:
    monitor = {"top" : 0, "left" : 0, "width" : infos.current_w, "height" : infos.current_h}
    
    while True:
        try:
            sock.connect((TCP_IP, TCP_PORT))
            print("Connect")
            break
        except:
            pass

    while True:
        img = np.array(sct.grab(monitor))

        encode_param = [int(cv2.IMWRITE_JPEG_QUALITY), 90]
        result, imgencode = cv2.imencode('.png', img, encode_param)
        data = np.array(imgencode)
        stringData = data.tostring()
        print(len(data))
        sock.send(stringData)
