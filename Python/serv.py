# 캡쳐화면 TCP/IP 통신
#
# -*- coding: utf-8 -*-

import socket
import time

import mss
import cv2
import numpy as np

TCP_IP = "192.168.100.1"
TCP_PORT = 30000

serv_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
serv_sock.bind((TCP_IP, TCP_PORT))
serv_sock.listen(0)
clnt_sock, addr = serv_sock.accept()

while True:
    stringData = clnt_sock.recv(99999999)

    data = np.fromstring(stringData, dtype = np.uint8)
    img = cv2.imdecode(data, 1)

    try:
        cv2.imshow("Screen", img)
    except:
        pass

    if cv2.waitKey(25) & 0xFF == ord('q'):
        cv2.destroyAllWindows()
        break

