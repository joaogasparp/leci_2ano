import socket
import threading
import signal
import sys

def signal_handler(sig, frame):
    print('\nDone!')
    sys.exit(0)

signal.signal(signal.SIGINT, signal_handler)
print('Press Ctrl+C to exit...')

def handle_client_connection(client_socket,address):
    print('Accepted connection from {}:{}'.format(address[0], address[1]))
    try:
        while True:
            request = client_socket.recv(1024)
            if not request:
                client_socket.close()
            else:
                msg = request.decode()
                msg_bytes = byt(client_socket,msg)
                global total_bytes
                total_bytes = total_bytes + msg_bytes
                print('Received {} from {}'.format(msg,ip_name))
                msg = ('ECHO: {} | Bytes sent form {}: {} | Total bytes: {}'.format(msg,ip_name,msg_bytes,total_bytes)).encode()
                client_socket.send(msg)
    except (socket.timeout, socket.error):
        print('Client {} error. Done!'.format(address))

def byt(client_socket,msg):
    buf = bytes(msg, "utf-8") + b'\0'
    client_socket.sendall(buf)
    client_bytes = len(buf)
    return client_bytes

ip_addr = socket.gethostbyname(socket.gethostname())
tcp_port = 5005
ip_name = socket.gethostname()
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind((ip_addr, tcp_port))
server.listen()
total_bytes = 0

print('Listening on {}:{}'.format(ip_addr, tcp_port))

while True:
    client_sock,address = server.accept()
    client_handler = threading.Thread(target=handle_client_connection,args=(client_sock,address))
    client_handler.start()
    print("Active connections {}".format(threading.activeCount()-1))