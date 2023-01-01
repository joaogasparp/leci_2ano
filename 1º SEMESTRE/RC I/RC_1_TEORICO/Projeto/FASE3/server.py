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
    client_bytes = 0
    total_bytes = 0
    try:
        while True:
            request = client_socket.recv(1024).decode('utf-8')
            if not request:
                client_socket.close()
            else:
                request = int(request)
                msg = client_socket.recv(request).decode('utf-8')
                client_bytes += request
                print('Received {}'.format(msg))
                msg = ('Hostname: {} \nBytes sent form this Client: {} \nTotal bytes: {}\n'.format(ip_name,client_bytes,total_bytes()).encode('utf-8'))
                client_socket.send(msg)
    except (socket.timeout, socket.error):
        print('Client {} error. Done!'.format(address))
        
def total_bytes():
    return 0

ip_addr = socket.gethostbyname(socket.gethostname())
tcp_port = 5005
ip_name = socket.gethostname()
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind((ip_addr, tcp_port))
server.listen()
clients = []

print('Listening on {}:{}'.format(ip_addr, tcp_port))

while True:
    client_sock,address = server.accept()
    clients.append(client_sock,address)
    client_handler = threading.Thread(target=handle_client_connection,args=(client_sock,address))
    client_handler.start()