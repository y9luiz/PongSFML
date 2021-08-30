#include "game_server.h"

GameServer::GameServer(int port,bool blocking):port_(port)
{
	listener_.listen(port_);
	listener_.setBlocking(blocking);
	selector_.add(listener_);
}
bool GameServer::checkForNewConnections()
{
	if (selector_.isReady(listener_))
	{
		auto client = std::make_shared<sf::TcpSocket>();
		if (listener_.accept(*client))
		{
			numb_clients_++;
			clients_.push_back(client);
			selector_.add(*client);
			return true;
		}
	}
	return false;
}

void GameServer::receivePacketsFromClients()
{
	for ( auto & client : clients_)
	{
		if (selector_.isReady(*client))
		{
			// packet receive routine
			sf::Packet packet;
			if (client->receive(packet) == sf::Socket::Done)
			{
				//	from the clients we need the position of the 
				//  paddles

			}
		}
	}

}
void GameServer::sendPacketsToClients()
{
	for (auto& client : clients_)
	{
		if (selector_.isReady(*client))
		{
			// packet receive routine
			sf::Packet packet;
			if (client->receive(packet) == sf::Socket::Done)
			{
				//	from the clients we need the position of the 
				//  paddles

			}
		}
	}

}

