import socket

HOST = "192.168.4.1"
PORT = 3333

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))

s.sendall(b"F")   # Frente
#s.sendall(b"T") # Trás
#s.sendall(b"P") # Para

s.close()
