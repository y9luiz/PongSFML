#include <iostream>
#include <SFML/Network.hpp>

class Client
{
    public:
        Client()
        {
            socket.bind(5000);
        };

        void run();
        sf::UdpSocket socket;
};

void Client::run()
{
    std::cout << ">> Client running\n";

    while (true)
    {
        sf::Packet packet;

        sf::IpAddress senderIP = "127.0.0.1";
        unsigned short port = 5001;

        socket.receive(packet, senderIP, port);

        std::cout << packet << ", ";
    }
}

int main()
{
    std::cout << "::: UDP Socket :::\n";

    Client *client = nullptr;

    client = new Client();

    client->run();

    if (client != nullptr)
        delete client;

    return 0;
}