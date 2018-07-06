import socket

clntSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
clntSocket.connect(("127.0.0.1", 3000))

clntSocket.send("hello".encode())