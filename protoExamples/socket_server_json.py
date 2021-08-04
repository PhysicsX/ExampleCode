#!/usr/bin/env python3

import socket
from time import sleep
import json

HOST = '127.0.0.1'  # Standard loopback interface address (localhost)
PORT = 2389        # Port to listen on (non-privileged ports are > 1023)

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen()
    conn, addr = s.accept()
    with conn:
        print('Connected by', addr)
        while True:
            data = conn.recv(1024)
            if not data:
                break
            #x = '{"name":"John", "age":30, "city":"New York"}'

            data = data.decode('utf-8')
            print(data)
            #print(x)
            y = json.loads(data)

            print(y)
            print(y['action'])
            d = json.dumps(data)

            send_data = {}
            send_data['key'] = 'value'
            json_data = json.dumps(send_data)

            conn.sendall(bytes(json_data,encoding="utf-8"))
            