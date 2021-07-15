#include <iostream>
#include "example.pb.h"

#include <chrono>
#include <boost/asio.hpp>
#include <boost/array.hpp>

// nc localhost 2389
// nc -l localhost 2389
// g++ example_socket.cpp example.pb.cc example.pb.h `pkg-config --cflags --libs protobuf`

int main()
{

    auto const address = boost::asio::ip::make_address("127.0.0.1");
    auto const port = static_cast<unsigned short>(std::atoi("2389"));

    boost::asio::io_service io_service;
    boost::asio::ip::tcp::socket socket(io_service);
	//connection
	boost::system::error_code ec;
 	socket.connect( boost::asio::ip::tcp::endpoint( address, port ),ec);
    if(ec){std::cout<<ec.message()<<std::endl; return 1;}

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
        
        boost::system::error_code error;
	    //boost::asio::write( socket, boost::asio::buffer(buffer, size), error );
        socket.write_some(boost::asio::buffer(buffer, size),error);
        if(error)
	    {
		    std::cout << "send failed: " << error.message() << std::endl;
        }

        // getting response from server
        boost::array<char,1024> buf;

        size_t len = socket.read_some(boost::asio::buffer(buf), error);
    
        if( error ) {
            std::cout << "receive failed: " << error.message() << std::endl;
        }
        else {

            Person per2;
            per2.ParseFromArray(buf.data(), len);
            // std::cout<<per2.id()<<std::endl;
            // std::cout<<per2.anotherid()<<std::endl;
            // std::cout<<per2.number()<<std::endl;
            // std::cout<<per2.aid()<<std::endl;
            // std::cout<<per2.bid()<<std::endl;
            // std::cout<<per2.cid()<<std::endl;
            // std::cout<<per2.did()<<std::endl;
            // std::cout<<per2.eid()<<std::endl;
            // std::cout<<per2.fid()<<std::endl;
            // std::cout<<per2.gid()<<std::endl; 
        }


    }

    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << elapsed.count() << '\n';


    return 0;
}