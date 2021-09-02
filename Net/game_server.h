#pragma once
#include <SFML/network.hpp>
#include <SFML/System.hpp>
#include <list>
#include "../defs.h"
#include <queue>
#include <unordered_map>
class GameServer
{
	public:
		GameServer(int port = 5000,bool blocking = false);
		bool checkForNewConnections();
		void waitForClients();
		void notifyClients();
		void receivePacketsFromClients();
		void sendPacketToClients(sf::Packet& packet);
		void sendAllPacketsToClients(sf::Packet& packet);

	private:
		void updateGameState();
		sf::TcpListener listener_;
		
		std::unordered_map<std::string, std::shared_ptr<sf::TcpSocket>> clients_map_;
		std::queue<sf::Packet> in_packets_;
		std::queue<sf::Packet> out_packets_;

		bool blocking;
		int port_;
		static sf::Vector2f ball_position_;
		static sf::Vector2f ball_speed_;
		unsigned numb_clients_ = 0;
		const char addr_separator_ = '$';
};