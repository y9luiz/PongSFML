#include <iostream>
#include "Net/game_client.h"
#include <SFML/Network.hpp>

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cout << "usage ./PongTestClient <server_ip_address> <your_identity>\n";
		return 1;
	}

	GameClient game_client(argv[1]);
	
	game_client.connect();
	sf::Packet notification = game_client.receivePacket();
	bool start;
	notification >> start;
	if (!start)
	{
		std::cout << "could not start the client\n";
		return 1;
	}
	std::cout << "notification received\n";
	sf::Packet packet;
	std::string msg = "hello world from client ";
	msg += argv[2];
	msg += '\0';
	packet.append(msg.c_str(), msg.size());
	if (game_client.sendPacket(packet))
		std::cout << "good \n";
	char c = ' ';
	std::cout << "press q to finish the connection\n";
	while (c != 'q')
	{
		std::cin >> c;
	}
	return 0;
}