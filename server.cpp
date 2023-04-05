// Server code
#define BOOST_BIND_GLOBAL_PLACEHOLDERS

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
using namespace boost::placeholders;

using boost::asio::ip::tcp;
using namespace std;

//cmd code
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <algorithm>
#include <vector>
#include<sys/wait.h>
#include <functional>
#include<sys/stat.h>
/*void cmd_PWD(tcp::socket sock) {
        char cwdResponse[10000];
        getcwd(cwdResponse, sizeof(cwdResponse));
	    
}*/

//session code
void session(tcp::socket sock)
{
    try
    {
        for (;;)
        {
            // Read data from the client
            boost::asio::streambuf buffer;
            boost::asio::read_until(sock, buffer, '\n');
            std::string data = boost::asio::buffer_cast<const char*>(buffer.data());
            
            // Reverse the message
            std::reverse(data.begin(), data.end());
           // char cwdResponse[10000];
            //getcwd(cwdResponse, sizeof(cwdResponse));
            string dat;
            cin>>dat; 

            // Send the reversed message back to the client
            boost::asio::write(sock, boost::asio::buffer(data));
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception in thread: " << e.what() << "\n";
    }
}

int main()
{
    try
    {
        boost::asio::io_context io_context;
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 1234));

        for (;;)
        {
            tcp::socket socket(io_context);
            acceptor.accept(socket);

            std::thread(session, std::move(socket)).detach();
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}

