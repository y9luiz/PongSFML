#include <iostream>
#include <SFML/Network.hpp>

class Server
{
    public:
        Server()
        {
            value = 0;
            socket.bind(5001);
        };

        void run();
        sf::UdpSocket socket;

    private:
        int value;
};

void Server::run()
{
    std::cout << ">> Server running\n";
    std::cout << "Enter value: ";

    std::cin >> value;

    sf::Packet packet;
    packet << value;

    sf::IpAddress recieverIP = "127.0.0.1";
    unsigned short port = 5000;

    socket.send(packet, recieverIP, port);
}

int main()
{
    std::cout << "::: UDP Socket :::\n";

    Server *server = nullptr;

    server = new Server();

    server->run();
    
    if (server != nullptr)
        delete server;

    return 0;
}