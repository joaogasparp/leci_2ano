import socket
import threading

PORT= 5005
SERVER = socket.gethostname()
SERVER_ADDRESS = socket.gethostbyname(socket.gethostname())
ADDR =(SERVER_ADDRESS, PORT)
HEADER = 1024
FORMAT ='utf-8'
server = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
server.bind(ADDR)
clients = []

def handle_client(conn,addr):
    client_bytes = 0
    total_bytes = 0
    print(f"[New Connection] {addr} connected.")
    connected = True
    while connected:
        msg_length = conn.recv(HEADER).decode(FORMAT)
        if msg_length:   
            msg_length = int(msg_length)
            msg = conn.recv(msg_length).decode(FORMAT)
            client_bytes += msg_length
            print(f"[{addr} {msg}]")
            conn.send(f"Hostname : {SERVER} \nMessage Status: Received \nTotal bytes: {Total_Bytes()} \nBytes sent form this Client: {client_bytes}".encode(FORMAT))
    conn.close()

def Total_Bytes():
   return 0
    
def start():
    server.listen()
    print(f"[LISTENING] Server is listening on {SERVER_ADDRESS}")
    while True:
        conn, addr =server.accept()
        clients.append(conn,addr)
        thread = threading.Thread(target=handle_client,args = (conn,addr))
        thread.start()
        print(f"Active connections {threading.activeCount()-1}")

print("[STARTING] server is starting...")
start()