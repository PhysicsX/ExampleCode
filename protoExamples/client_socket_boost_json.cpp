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

//g++ client_socket_boost_json.cpp -lpthread -I /usr/include/boost -I /home/jnano/vcpkg/installed/x64-linux/include /home/jnano/vcpkg/installed/x64-linux/lib/objects-Release/jsoncpp_object/json_value.cpp.o /home/jnano/vcpkg/installed/x64-linux/lib/objects-Release/jsoncpp_object/json_writer.cpp.o /home/jnano/vcpkg/installed/x64-linux/lib/objects-Release/jsoncpp_object/json_reader.cpp.o -o jsonSocket

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
        //std::cout << json_file << std::endl;
        boost::system::error_code error;
        socket.write_some(boost::asio::buffer(json_file.c_str(), json_file.size()),error);
        if(error)
        {
            std::cout << "send failed: " << error.message() << std::endl;
        }

        boost::array<char,1024> buf;

        size_t len = socket.read_some(boost::asio::buffer(buf), error);
        std::cout<<len<<std::endl;
        std::string str;

        std::copy(buf.begin(), buf.begin()+len, std::back_inserter(str));
        
        Json::Value read;
        //const std::string rawJson = R"({"Age": 20, "Name": "colin"})";
        Json::CharReaderBuilder builderRead;
        JSONCPP_STRING err;
        const std::unique_ptr<Json::CharReader> reader(builderRead.newCharReader());
        if (!reader->parse(str.c_str(), str.c_str() + str.size(), &read,
                        &err)) {
        std::cout << "error" << std::endl;
        }

        //std::cout << read["id2"] << std::endl;
    }

    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << elapsed.count() << '\n';

    return 0;
}