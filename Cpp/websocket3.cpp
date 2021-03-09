#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <string>
#include <thread>
// g++ -I /usr/include/boost -pthread websocket.cpp 
namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

//------------------------------------------------------------------------------

int main(int argc, char* argv[])
{

        auto const address = net::ip::make_address("192.168.56.102");
        auto const port = static_cast<unsigned short>(std::atoi("8080"));

        net::io_context ioc{1};

        tcp::acceptor acceptor{ioc, {address, port}};
        for(;;)
        {

            tcp::socket socket{ioc};

            acceptor.accept(socket);

            std::thread{std::bind(
                //[q = std::move(socket)]() mutable { // socket will be const - mutable should be used
                [q{std::move(socket)}]() { // socket will be const - mutable should be used
                     
                
                     
                websocket::stream<tcp::socket> ws{std::move(const_cast<tcp::socket&>(q))};
                    
                // Set a decorator to change the Server of the handshake
                ws.set_option(websocket::stream_base::decorator(
                    [](websocket::response_type& res)
                    {
                        res.set(http::field::server,
                        std::string(BOOST_BEAST_VERSION_STRING) +
                            " websocket-server-sync");
                                }));

                        // Accept the websocket handshake
                        ws.accept();

                        while(true)
                        {
                            try
                            {
                                       
                            // This buffer will hold the incoming message
                            beast::flat_buffer buffer;

                            // Read a message
                            ws.read(buffer);

                            auto out = beast::buffers_to_string(buffer.cdata());
                            std::cout << out << std::endl;

                            // Echo the message back
                            //ws.text(ws.got_text());
                            //bost::beast::ostream(buffer) << "something";
                            ws.write(buffer.data());
                            }
                            catch(beast::system_error const& se)
                            {
                                if(se.code() != websocket::error::closed)
                                {
                                    std::cerr << "Error: " << se.code().message() << std::endl;
                                    break;
                                }
                            }
                        }
                }
            )}.detach();
        }
}