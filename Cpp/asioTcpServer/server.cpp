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

int main() 
{
	boost::asio::io_service io_service;
	//listen for new connection
	boost::system::error_code ec;
      	boost::asio::ip::tcp::acceptor acceptor_(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 1234 )); 
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
