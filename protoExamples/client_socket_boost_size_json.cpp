#include <iostream>
#include <assert.h>

#include <chrono>
#include <boost/asio.hpp>
#include <boost/array.hpp>

#include "json/json.h"
#include <iomanip>
// nc localhost 2389
// nc -l localhost 2389
// g++ example_socket.cpp example.pb.cc example.pb.h `pkg-config --cflags --libs protobuf`

//g++ client_socket_boost_size_json.cpp -lpthread -I /usr/include/boost -I /home/jnano/vcpkg/installed/x64-linux/include /home/jnano/vcpkg/installed/x64-linux/lib/objects-Release/jsoncpp_object/json_value.cpp.o /home/jnano/vcpkg/installed/x64-linux/lib/objects-Release/jsoncpp_object/json_writer.cpp.o /home/jnano/vcpkg/installed/x64-linux/lib/objects-Release/jsoncpp_object/json_reader.cpp.o -o jsonSocket


// nc localhost 2389
// nc -l localhost 2389
// g++ client_socket_boost_size_json.cpp example.pb.cc example.pb.h `pkg-config --cflags --libs protobuf`

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
        Json::Value root;

        root["id"] = "5000";
        root["id2"] = "5000";
        root["id3"] = "5000";
        root["id4"] = "5000";
        root["id5"] = "5000";
        root["id6"] = "5000";
        root["id7"] = "5000";
        root["id8"] = "5000";
        root["id9"] = "5000";
        root["id10"] = "5000";


        Json::StreamWriterBuilder builder;
        const std::string json_file = Json::writeString(builder, root);
        //std::cout << json_file.size() << std::endl;

        boost::system::error_code error;
	    boost::asio::write( socket, boost::asio::buffer(json_file.c_str(), json_file.size()), error );

        if(error)
	    {
		    std::cout << "send failed: " << error.message() << std::endl;
        }


        // getting response from server
        boost::asio::streambuf receive_buffer;
        size_t len = 150;
        boost::asio::read(socket, receive_buffer,boost::asio::transfer_exactly(len), error);

        if( error ) {
            std::cout << "receive failed: " << error.message() << std::endl;
        }
        else {

            //https://stackoverflow.com/questions/877652/copy-a-streambufs-contents-to-a-string
            boost::asio::streambuf::const_buffers_type bufs = receive_buffer.data();
            std::string str(boost::asio::buffers_begin(bufs),
                            boost::asio::buffers_begin(bufs) + len);

            const char* data = boost::asio::buffer_cast<const char*>(receive_buffer.data());

            Json::Value read;
            //const std::string rawJson = R"({"Age": 20, "Name": "colin"})";
            Json::CharReaderBuilder builderRead;
            JSONCPP_STRING err;
            const std::unique_ptr<Json::CharReader> reader(builderRead.newCharReader());
            if (!reader->parse(str.c_str(), str.c_str() + len, &read,
                            &err)) {
            std::cout << "error" << std::endl;
            }

            // std::cout << read["id"] << std::endl;
            // std::cout << read["id2"] << std::endl;
            // std::cout << read["id3"] << std::endl;
            // std::cout << read["id4"] << std::endl;
            // std::cout << read["id5"] << std::endl;
            // std::cout << read["id6"] << std::endl;
            // std::cout << read["id7"] << std::endl;
            // std::cout << read["id8"] << std::endl;
            // std::cout << read["id9"] << std::endl;
            // std::cout << read["id10"] << std::endl;
        }


    }

    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << elapsed.count() << '\n';


    return 0;
} 