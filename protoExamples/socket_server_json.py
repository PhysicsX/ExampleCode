#!/usr/bin/env python3

import socket
from time import sleep
import json
import sys

HOST = '127.0.0.1'  # Standard loopback interface address (localhost)
PORT = 2389        # Port to listen on (non-privileged ports are > 1023)

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen()
    conn, addr = s.accept()
    with conn:
        print('Connected by', addr)
        while True:
            data = conn.recv(172)
            if not data:
                break

            data = data.decode('utf-8')
            #print(data)
            d = json.dumps(data)

            send_data = {}
            send_data['id'] = '5001'
            send_data['id2'] = '5001'
            send_data['id3'] = '5001'
            send_data['id4'] = '5001'
            send_data['id5'] = '5001'
            send_data['id6'] = '5001'
            send_data['id7'] = '5001'            
            send_data['id8'] = '5001'
            send_data['id9'] = '5001'
            send_data['id10'] = '5001'

            json_data = json.dumps(send_data)
            #print(sys.getsizeof(json_data))

            conn.sendall(bytes(json_data,encoding="utf-8"))
            