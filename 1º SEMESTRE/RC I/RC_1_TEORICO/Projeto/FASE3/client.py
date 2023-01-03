import socket
import signal
import sys

def signal_handler(sig, frame):
    print('\nDone!')
    sys.exit(0)
    
signal.signal(signal.SIGINT, signal_handler)
print('Press Ctrl+C to exit...')

ip_addr = "120.100.20.10"
ip_name = socket.gethostname()
tcp_port = 5005
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect((ip_addr, tcp_port))

print('Hostname: {} | IP Address: {}'.format(ip_name,ip_addr))

while True:
    try:
        message = input("Your message ({})-> ".format(ip_name))
        msg = message.encode()
        sock.send(msg)
        response = sock.recv(4096).decode()
        print('Server response-> {}'.format(response))
        
    except (socket.timeout, socket.error):
        print('Server error. Done!')
        sys.exit(0)