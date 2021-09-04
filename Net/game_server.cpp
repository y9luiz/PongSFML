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
void GameServer::notifyClients()
{
	unsigned client_idx=0;
	for (auto& client_pair : clients_map_)
	{
		GamePacket packet;
		packet << client_idx++;
		sendPacketToClient(packet, client_pair.first);

	}
	std::cout << "cliente idx " << client_idx << "\n";
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
void GameServer::sendPacketToClient(GamePacket& packet, const std::string & ip)
{
	if (clients_map_[ip]->send(packet) == sf::Socket::Done)
	{
		std::cout << "packet sent\n";
	}
	else {
		std::cout << "packet not sented\n";
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

	std::shared_ptr <Ball> ball = std::make_shared <Ball>(BALL_INIT_POSITION,BALL_RADIUS);
	ball->setSpeed(BALL_SPEED);

	std::shared_ptr<Paddle> player1 = std::make_shared<Paddle>(PLAYER_1_RECT);
	std::shared_ptr <Paddle> player2 = std::make_shared<Paddle>(PLAYER_2_RECT);
	
	std::vector<std::shared_ptr<sf::Shape>> game_objects;

	game_objects.push_back(player1);
	game_objects.push_back(player2);

	while (running_)
	{
		ball_position_ = ball->getPosition(); // push ball position
		GamePacket ball_position_pack;
		ball_position_pack << ball_position_;
		
		sendPacketToClients(ball_position_pack);
		//out_packets_.push(ball_position_pack);
		sf::Vector2f ball_pos_test;
		ball_position_pack >> ball_pos_test;
		std::cout << ball_pos_test.x << ": " << ball_pos_test.y << "\n";
		std::cout << ball_position_.x <<": "<< ball_position_.y << "\n";

		/* Receive paddles position
		*	receive packages with the position of each client
		*/
		receivePacketsFromClients(); // this function also addeds the client address at the end of packet

		int idx = 0;

		std::string player1_ip;
		GamePacket player1_packet_pos;

		std::string player2_ip;
		GamePacket player2_packet_pos;

		for (const auto& client_pair : clients_map_)
		{
			if (idx == 0)
			{
				player1_ip = client_pair.first;
				player1_packet_pos = in_packets_.front();
				sf::Vector2f pos(0, 0);
				player1_packet_pos >> pos;
				player2->setPosition(pos);
			}
			else if(idx == 1){
				player2_ip = client_pair.first;
				player2_packet_pos = in_packets_.front();
				sf::Vector2f pos(0, 0);
				player2_packet_pos >> pos;
				player2->setPosition(pos);
			}
			in_packets_.pop();

			idx++;
		}
		clients_map_[player1_ip]->send(player2_packet_pos);
		clients_map_[player2_ip]->send(player1_packet_pos);
		
		autoMove(*ball);
		ball->checkCollision(game_objects);
		
		std::this_thread::sleep_for(33ms);

	}
}