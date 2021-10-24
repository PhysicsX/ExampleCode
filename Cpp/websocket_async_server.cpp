#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <iostream>
#include <memory>
#include <string>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

// g++ -std=c++17 -I /usr/include/boost -pthread websocket_async_server.cpp

class EchoWebsocket : public std::enable_shared_from_this<EchoWebsocket>
{
    websocket::stream<beast::tcp_stream> ws;
    beast::flat_buffer buffer;

public:

    EchoWebsocket(tcp::socket&& socket)
        : ws(std::move(socket))
    {
    }

    void
    run()
    {
        ws.async_accept(
            [self{shared_from_this()}](beast::error_code ec){

                if(ec){ std::cout << ec.message() << "\n"; return;}

                self->echo();
            });  
    }

    void
    echo()
    {
            ws.async_read(
            buffer,
            [self{shared_from_this()}](beast::error_code ec, std::size_t bytes_transferred)
            {
                if(ec == websocket::error::closed)
                    return;

                if(ec){ std::cout << ec.message() << "\n"; return;}

                auto out = beast::buffers_to_string(self->buffer.cdata());
                std::cout<<out<<" "<<std::flush;
                self->ws.async_write(
                     self->buffer.data(),
                     [self](beast::error_code ec, std::size_t bytes_transferred)
                     {

                        if(ec){ std::cout << ec.message() << "\n"; return;}

                        self->buffer.consume(self->buffer.size());

                        self->echo();
                     });
            });
    }

};

class Listener : public std::enable_shared_from_this<Listener>
{
    net::io_context& ioc;
    tcp::acceptor acceptor;

public:
    Listener(
        net::io_context& ioc,
        unsigned short int port
        )
        : ioc(ioc)
        , acceptor(ioc, {net::ip::make_address("127.0.0.1"), port}){}

    void
    asyncAccept()
    {
        acceptor.async_accept(
            ioc,
            [self{shared_from_this()}](boost::system::error_code ec, tcp::socket socket) {
                
                std::make_shared<EchoWebsocket>(std::move(socket))->run();

                self->asyncAccept();
                });
    }

};

int main(int argc, char* argv[])
{

    auto const port = static_cast<unsigned short int>(std::atoi("8083"));
    net::io_context ioc{};

    std::make_shared<Listener>(ioc,port)->asyncAccept();

    ioc.run();

    return 0;
}