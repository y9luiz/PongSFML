#pragma once
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <list>
#include "../defs.h"
#include <queue>
#include <unordered_map>
#include <memory>
#include "game_packet.h"
class GameServer
{
	public:
		GameServer(int port = 5000,bool blocking = false);
		bool checkForNewConnections();
		void waitForClients();
		void notifyClients();
		void receivePacketsFromClients();
		void sendPacketToClients(GamePacket& packet);
		void sendPacketToClient(GamePacket& packet, const std::string& ip);
		void run();
		static sf::Vector2f ball_position_;
		static sf::Vector2f ball_speed_;
		static int numb_clients_;
	private:

		void updateGameState();
		sf::TcpListener listener_;
		std::unordered_map<std::string, std::shared_ptr<sf::TcpSocket>> clients_map_;
		std::queue<GamePacket> in_packets_;

		bool blocking;
		int port_;
		bool running_;
		bool checkOutOfLimitsBoundary(std::shared_ptr<sf::Shape> obj);
		const char addr_separator_ = '$';
};
