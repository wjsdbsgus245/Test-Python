# 캡쳐화면 TCP/IP 통신
#
# -*- coding: utf-8 -*-

import socket
import time

import mss
import cv2
import numpy

def recvall(sock, count):
    buf = b''
    while count:
        newbuf = sock.recv(count)
        if not newbuf: return None
        buf += newbuf
        count -= len(newbuf)
    return buf

TCP_IP = "localhost"
TCP_PORT = 30000

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((TCP_IP, TCP_PORT))
s.listen(True)
conn, addr = s.accept()

length = recvall(conn, 16)
stringData = recvall(conn, int(length))
data = numpy.fromstring(stringData, dtype = "uint8")
s.close()

img = cv2.imdecode(data, 1)
cv2.imshow("Server", img)
cv2.waitKey(0)
cv2.destroyAllWindows()
