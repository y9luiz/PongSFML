#pragma once
#include <SFML/network.hpp>
#include <SFML/System.hpp>
#include <string>
#include <memory>
class GameClient
{
	public:
		GameClient(const std::string &  address, unsigned int port = 5000, bool blocking = true);
		bool connect();
		bool sendPacket( sf::Packet& packet);
		sf::Packet receivePacket();
	private:
		std::string address_;
		unsigned int port_;
		std::shared_ptr<sf::TcpSocket> socket_;
};