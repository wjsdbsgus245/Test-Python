# 캡쳐화면 TCP/IP 통신
#
# -*- coding: utf-8 -*-

import socket
import time

import mss
import cv2
import numpy

UDP_IP = "localhost"
UDP_PORT = 30000

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((UDP_IP, UDP_PORT))

data, addr = sock.recvfrom(65535)
print("Server is received data : {0}".format(data.decode()))
print("Send Client IP : {0}".format(addr[0]))
print("Send Client Port : {0}".format(addr[1]))
