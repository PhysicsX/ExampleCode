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

    Json::Value root;
    Json::Value data;

    root["action"] = "run";
    data["number"] = 1;
    root["data"] = data;

    Json::StreamWriterBuilder builder;
    const std::string json_file = Json::writeString(builder, root);
    std::cout << json_file << std::endl;

    auto const address = boost::asio::ip::make_address("127.0.0.1");
    auto const port = static_cast<unsigned short>(std::atoi("2389"));

    boost::asio::io_service io_service;
    boost::asio::ip::tcp::socket socket(io_service);
	//connection
	boost::system::error_code ec;
 	socket.connect( boost::asio::ip::tcp::endpoint( address, port ),ec);
    if(ec){std::cout<<ec.message()<<std::endl; return 1;}

    size_t size = sizeof(json_file.c_str()) / sizeof(json_file.c_str()[0]);
    //std::cout<<size;
    boost::system::error_code error;
	//boost::asio::write( socket, boost::asio::buffer(buffer, size), error );
    socket.write_some(boost::asio::buffer(json_file.c_str(), json_file.size()),error);
    if(error)
	{
	    std::cout << "send failed: " << error.message() << std::endl;
    }

    boost::array<char,1024> buf;

    size_t len = socket.read_some(boost::asio::buffer(buf), error);
    
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

    //const std::string age = read["action"].asString();
    std::cout << read["key"] << std::endl;

    return 0;
}