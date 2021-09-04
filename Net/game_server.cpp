#include "game_server.h"
#include <chrono>
#include <thread>
#include <iostream>
#include "../ball.h"
#include "../paddle.h"
//#include "../utils.h"
using namespace std::chrono_literals;
int GameServer::numb_clients_ = 0;
sf::Vector2f GameServer::ball_position_ = sf::Vector2f(0, 0);
sf::Vector2f GameServer::ball_speed_ = sf::Vector2f(0, 0);

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
		std::string ip = client->getRemoteAddress().toString();
		std::pair<std::string, std::shared_ptr<sf::TcpSocket>> client_pair(ip,client);
		if (clients_map_.find(ip) == clients_map_.end())
		{
			clients_map_.insert(client_pair);
			return true;
		}
		std::cout << ip << " already added\n";
	}
	
	return false;
}
void GameServer::waitForClients()
{
	while (numb_clients_ < 2)
	{
		if (checkForNewConnections())
		{
			numb_clients_++;
		}
		
		std::this_thread::sleep_for(1ms);
	}

}
unsigned client_idx = 0;
void GameServer::notifyClients()
{
	GamePacket packet;
	packet << client_idx++;
	std::cout << "cliente idx " << client_idx << "\n";
	sendPacketToClients(packet);
}
void GameServer::receivePacketsFromClients()
{
	
	for (auto& client_pair : clients_map_)
	{
		std::cout << "receiving packets from client " << client_pair.first << "\n";

		auto client = client_pair.second;

		// packet receive routine
		GamePacket packet;
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
void GameServer::sendPacketToClients(GamePacket & packet )
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
void GameServer::sendAllPacketsToClients()
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

void GameServer::run()
{
	running_ = true;

	Ball ball(BALL_INIT_POSITION,BALL_RADIUS);
	ball.setSpeed(BALL_SPEED);

	Paddle player1(PLAYER_1_RECT);
	Paddle player2(PLAYER_2_RECT);
	
	while (running_)
	{
		// send the ball position
		ball_position_ = ball.getPosition();
		GamePacket ball_position_pack;
		ball_position_pack << ball_position_;
		
		out_packets_.push(ball_position_pack);
		sf::Vector2f ball_pos_test;
		ball_position_pack >> ball_pos_test;
		std::cout << ball_pos_test.x << ": " << ball_pos_test.y << "\n";
		std::cout << ball_position_.x <<": "<< ball_position_.y << "\n";

		/*
		*	receive packages with the position of each client
		*/
		receivePacketsFromClients(); // this function also addeds the client address at the end of packet

		int idx = 0;
		for (const auto& client_pair : clients_map_)
		{
			auto pos = sf::Vector2f(0, 0);
			auto game_packet = in_packets_.front();
			out_packets_.push(game_packet);
			game_packet >> pos;

			if (idx == 0)
			{
				player1.setPosition(pos);
			}
			else if(idx == 1)
			{
				player2.setPosition(pos);
			}
			idx++;
		}
		
		autoMove(ball);

		sendAllPacketsToClients();

		std::this_thread::sleep_for(33ms);

	}
}