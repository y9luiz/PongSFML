#include "game_server.h"
#include <chrono>
#include <thread>
#include <iostream>
using namespace std::chrono_literals;
GameServer::GameServer(int port,bool blocking):port_(port)
{
	listener_.setBlocking(blocking);
	listener_.listen(port_);
}
bool GameServer::checkForNewConnections()
{	
	auto client = std::make_shared<sf::TcpSocket>();
	if (listener_.accept(*client) == sf::Socket::Done)
	{
		numb_clients_++;
		std::string ip = client->getRemoteAddress().toString();
		std::pair<std::string, std::shared_ptr<sf::TcpSocket>> client_pair(ip,client);
		clients_map_.insert(client_pair);
		return true;
	}
	
	return false;
}
void GameServer::waitForClients()
{
	while (numb_clients_ < 2)
	{
		checkForNewConnections();
		std::this_thread::sleep_for(1ms);
	}
}
void GameServer::notifyClients()
{
	sf::Packet packet;
	packet << true;
	sendPacketToClients(packet);
}
void GameServer::receivePacketsFromClients()
{
	
	for (auto& client_pair : clients_map_)
	{
		std::cout << "receiving packets from client " << client_pair.first << "\n";

		auto client = client_pair.second;

		// packet receive routine
		sf::Packet packet;
		if (client->receive(packet) == sf::Socket::Done)
		{
			std::cout << "packet received...\n";
			std::cout << (char*)packet.getData() << "\n";
			std::string address;
			address += addr_separator_;
			address += client->getRemoteAddress().toString();

			// append the ip to the end of packet
			packet.append(address.c_str(), address.size());
			//	from the clients we need the position of the 
			//  respective paddle
			in_packets_.push(packet);

		}

	}
}
void GameServer::sendPacketToClients(sf::Packet & packet )
{
	for (auto& client_pair : clients_map_)
	{
		auto client = client_pair.second;
		
		// packet send routine
		if (client->send(packet) == sf::Socket::Done)
		{
			std::cout << "packet sent\n";
			//	we need to send the ball position to the client
		}
		
	}

}
void GameServer::sendAllPacketsToClients(sf::Packet& packet)
{
	while (!out_packets_.empty())
	{
		auto packet = out_packets_.front();
		sendPacketToClients(packet);
		out_packets_.pop();
	}
}

void GameServer::updateGameState()
{
	while (!in_packets_.empty())
	{
		/*auto packet = in_packets_.front();
		std::string str = (char *) packet.getData();
		auto splitted_data = splitString(str, addr_separator_);
		
		sf::IpAddress ip(splitted_data.back());
		auto position = stdStringTosfVector(splitted_data[0]);
		
		in_packets_.pop();*/
	}
}