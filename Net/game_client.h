#pragma once
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <string>
#include <memory>
#include "game_packet.h"
class GameClient
{
	public:
		GameClient(const std::string &  address, unsigned int port = 5000, bool blocking = true);
		bool connect();
		bool isConnected()
		{
			return is_connected_;
		}
		bool sendPacket( sf::Packet& packet);
		// retrive the player index, which represents
		// which paddle this paddle is
		//	 0 is the left
		//	 1 is the right
		void waitForPlayerIndex();
		GamePacket receivePacket();
		uint8_t getPlayerIndex()
		{
			return player_idx_;
		}
	private:
		std::string address_;
		unsigned int port_;
		std::shared_ptr<sf::TcpSocket> socket_;
		bool is_connected_ = false;
		uint8_t player_idx_;
};
