//simple tcp socket server example with boost asio
//sudo apt install libboost-dev
//g++ -lpthread -lboost_system server.cpp -o server

#include <iostream>
#include <boost/asio.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/strand.hpp>

//using namespace boost::asio
//using ip::tcp

using std::string;
using std::cout;
using std::endl;

int main(int argc, char* argv[]) 
{

	if(argc != 3)
	{
		std::cout<<"Wrong parameter\n"<<"Example usage 127.0.0.1 1234"<<std::endl;	
		return -1;
	}

	auto const address = boost::asio::ip::make_address(argv[1]);
	auto const port = std::atoi(argv[2]);

	

	boost::asio::io_service io_service;
	//listen for new connection
	boost::system::error_code ec;
      	boost::asio::ip::tcp::acceptor acceptor_(io_service, boost::asio::ip::tcp::endpoint(address, port )); 
	boost::asio::ip::tcp::socket socket_(io_service);//socket creation	
	acceptor_.accept(socket_);//waiting for connection
	//read operation
	boost::asio::streambuf buf;
	boost::asio::read_until( socket_, buf, "\n",ec);
	if(ec){std::cout<<ec.message()<<std::endl; return 1;}	
	string data = boost::asio::buffer_cast<const char*>(buf.data());
	cout << data << endl;
	//write operation
	boost::asio::write( socket_, boost::asio::buffer(data) ,ec);
	if(ec){std::cout<<ec.message()<<std::endl; return 1;}		
	return 0;
}
