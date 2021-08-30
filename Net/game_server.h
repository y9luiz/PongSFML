#pragma once
#include <SFML/network.hpp>
#include <SFML/System.hpp>
#include <list>
#include "../defs.h"
class GameServer
{
	public:
		GameServer(int port = 5000,bool blocking = false);
		bool checkForNewConnections();
		void receivePacketsFromClients();
		void sendPacketsToClients();

	private:

		sf::TcpListener listener_;
		std::list<std::shared_ptr<sf::TcpSocket>> clients_;
		sf::SocketSelector selector_;
		bool blocking;
		int port_;
		static sf::Vector2f ball_position_;
		static sf::Vector2f ball_speed_;
		unsigned numb_clients_ = 0;
};