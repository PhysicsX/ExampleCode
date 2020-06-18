//importing libraries
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <memory>

using namespace boost::asio;
using ip::tcp;
using std::cout;
using std::endl;


class con_handler : public std::enable_shared_from_this<con_handler>
{
private:
  tcp::socket sock;
  std::string msg;
  enum { max_length = 10 };
  char data[max_length];

public:
  con_handler(boost::asio::io_service& io_service): sock(io_service){}
//socket creation
  tcp::socket& socket()
  {
    return sock;
  }

  void read()
  {
    sock.async_read_some(
        boost::asio::buffer(data, max_length),
        boost::bind(&con_handler::handle_read,
                    shared_from_this(),
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));

  }

 void write()
 {

	msg =  data;
	sock.async_write_some(
		boost::asio::buffer(msg, max_length),
		boost::bind(&con_handler::handle_write,
		          shared_from_this(),
		          boost::asio::placeholders::error,
		          boost::asio::placeholders::bytes_transferred));

 }

  void handle_read(const boost::system::error_code& err, size_t bytes_transferred)
  {
    if (!err) {
         cout << data << endl;
    } else {
         std::cerr << "error: " << err.message() << std::endl;
         sock.close();
    }
	write();
  }
  void handle_write(const boost::system::error_code& err, size_t bytes_transferred)
  {
    if (err) 
    {
       std::cerr << "error: " << err.message() << endl;
       sock.close();
    }
  }
};

class Server 
{
private:
   tcp::acceptor acceptor_;
	boost::asio::io_service &io_service;	
   void start_accept()
   {
    // socket
     //con_handler::pointer connection = con_handler::create(acceptor_.get_io_service());

	std::shared_ptr<con_handler> con = std::make_shared<con_handler>(io_service);
	
    // asynchronous accept operation and wait for a new connection.
     acceptor_.async_accept(con->socket(),
        boost::bind(&Server::handle_accept, this, con,
        boost::asio::placeholders::error));
  }
public:
//constructor for accepting connection from client
  Server(boost::asio::io_service& io_service): acceptor_(io_service, tcp::endpoint(tcp::v4(), 1234)),io_service(io_service)
  {
     start_accept();
  }
  void handle_accept(std::shared_ptr<con_handler> con, const boost::system::error_code& err)
  {
    if (!err) {
      con->read();
    }
    start_accept();
  }
};


int main(int argc, char *argv[])
{
  try
    {
    boost::asio::io_service io_service;  
    Server server(io_service);
    io_service.run();
    }
  catch(std::exception& e)
    {
    std::cerr << e.what() << endl;
    }
  return 0;
}
