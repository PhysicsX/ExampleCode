#!/usr/bin/env python3

import socket
from time import sleep
import example_pb2

HOST = '127.0.0.1'  # Standard loopback interface address (localhost)
PORT = 7000        # Port to listen on (non-privileged ports are > 1023)

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
            
            example = example_pb2.Person()
            example.ParseFromString(data)
            #print ("Person ID:", example.id)
            #print ("Person ID:", example.number)
            #print ("Person ID:", example.anotherId)
            #print ("Person ID:", example.aid)
            #print ("Person ID:", example.bid)
            #print ("Person ID:", example.cid)
            #print ("Person ID:", example.did)
            #print ("Person ID:", example.eid)
            #print ("Person ID:", example.fid)
            #print ("Person ID:", example.gid)

            write = example_pb2.Person()
            write.id = 5001
            write.number = 5001
            write.anotherId = 5001
            write.aid = 5001
            write.bid = 5001
            write.cid = 5001
            write.did = 5001
            write.eid = 5001
            write.fid = 5001
            write.gid = 5001
            out = write.SerializeToString()
   

            conn.sendall(out)
            #sleep(0.01)
            