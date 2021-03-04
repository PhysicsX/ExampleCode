// g++ -I /usr/include/boost -pthread websocket.cpp 


#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <string>
#include <thread>
#include <cassert>
#include <memory>
#include <utility>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>


int main(int argc, char* argv[])
{
        // Check command line arguments.
        if (argc != 3)
        {
            std::cerr <<
                "Usage: websocket-server-sync <address> <port>\n" <<
                "Example:\n" <<
                "    websocket-server-sync 0.0.0.0 8080\n";
            return EXIT_FAILURE;
        }
        auto const address = net::ip::make_address(argv[1]);
        auto const port = static_cast<unsigned short>(std::atoi(argv[2]));

        // The io_context is required for all I/O
        net::io_context ioc{1};

        // The acceptor receives incoming connections
        tcp::acceptor acceptor{ioc, {address, port}};
        while(true)
        {
            // This will receive the new connection
            tcp::socket socket{ioc};

            // Block until we get a connection
            acceptor.accept(socket);

            // Launch the session, transferring ownership of the socket
           
            auto session = [](tcp::socket socket){

                // Construct the stream by moving in the socket
                websocket::stream<tcp::socket> ws{std::move(socket)};

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
                            // This buffer will hold the incoming message
                            beast::flat_buffer buffer;

                            // Read a message
                            ws.read(buffer);

                            // Echo the message back
                            ws.text(ws.got_text());
                            ws.write(buffer.data());
                        }
            };

            std::thread(session, std::move(socket)).detach();
        }
}
