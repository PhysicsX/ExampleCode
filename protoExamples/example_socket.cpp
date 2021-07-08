#include <iostream>
#include "example.pb.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>

#include <chrono>

#define MYPORT  7000
#define BUFFER_SIZE 1024
// nc localhost 2389
// nc -l localhost 2389
// g++ example_socket.cpp example.pb.cc example.pb.h `pkg-config --cflags --libs protobuf`

int main()
{

    /// Define sockfd
    int sock_cli = socket(AF_INET,SOCK_STREAM, 0);

    /// Define sockaddr_in
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(MYPORT);  /// Server Port
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");  /// server ip

    Person per;
    per.set_id(5000);
    per.set_number(5000);
    per.set_anotherid(5000);
    per.set_aid(5000);
    per.set_bid(5000);
    per.set_cid(5000);
    per.set_did(5000);    
    per.set_eid(5000);    
    per.set_fid(5000);    
    per.set_gid(5000);    
    //per.set_name("MadamCurie");
    //gper.clear_name();
    //std::cout<<per.name();
    endl(std::cout);
    size_t size = per.ByteSizeLong();
    std::cout<<"size bytes "<<size<<std::endl;
    void *buffer = malloc(size);
    bool flag = per.SerializeToArray(buffer, size);
    if(flag == false)
        std::cout<<"serialize problem"<<std::endl;

    //Connect to the server, successfully return 0, error return - 1
    if (connect(sock_cli, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("connect");
        exit(1);
    }

    char sendbuf[size];
    char recvbuf[size];
    auto start = std::chrono::system_clock::now();
    int cnt = 0;
    while (cnt < 100000)
    {
        cnt ++;
        Person per;
        per.set_id(5000);
        per.set_number(5000);
        per.set_anotherid(5000);
        per.set_aid(5000);
        per.set_bid(5000);
        per.set_cid(5000);
        per.set_did(5000);    
        per.set_eid(5000);    
        per.set_fid(5000);    
        per.set_gid(5000);    

        size_t size = per.ByteSizeLong();

        void *buffer = malloc(size);
        bool flag = per.SerializeToArray(buffer, size);
        if(flag == false)
            std::cout<<"serialize problem"<<std::endl;

        send(sock_cli, buffer, size,0); /// Send

        recv(sock_cli, recvbuf, sizeof(recvbuf),0); /// Receiving
        //fputs(recvbuf, stdout);
        Person per2;
        per2.ParseFromArray(recvbuf, sizeof(recvbuf));
        //std::cout<<per2.id()<<std::endl;
        //std::cout<<per2.number()<<std::endl;
        
        memset(sendbuf, 0, sizeof(sendbuf));
        memset(recvbuf, 0, sizeof(recvbuf));
    }

    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << elapsed.count() << '\n';

    close(sock_cli);


    return 0;
}