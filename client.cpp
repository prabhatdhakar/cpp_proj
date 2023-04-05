// Client code

#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main()
{
    try
    {
        boost::asio::io_context io_context;

        // Connect to the server
        tcp::resolver resolver(io_context);
        tcp::resolver::results_type endpoints = resolver.resolve("localhost", "1234");
        tcp::socket socket(io_context);
        boost::asio::connect(socket, endpoints);

        for (;;)
        {
            // Read a message from the user
            std::string message;
            std::cout << "Enter a message: ";
            std::getline(std::cin, message);

            // Send the message to the server
            boost::asio::write(socket, boost::asio::buffer(message + "\n"));

            // Read the reversed message from the server
            boost::asio::streambuf buffer;
            boost::asio::read_until(socket, buffer, '\n');
            std::string reversed_message = boost::asio::buffer_cast<const char*>(buffer.data());

            std::cout << "Reversed message: " << reversed_message<<"\n";
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}

