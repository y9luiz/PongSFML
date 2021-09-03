#include "game_client.h"
GameClient::GameClient(const std::string& address, unsigned int port, bool blocking )
	: address_(address),port_(port)
{
	socket_ = std::make_shared<sf::TcpSocket>();
	socket_->setBlocking(blocking);

}

bool GameClient::connect()
{
	sf::IpAddress ip_address(address_);
	auto status = socket_->connect(ip_address, port_);
	is_connected_ = status == sf::TcpSocket::Done;
	return is_connected_;
}

bool GameClient::sendPacket(sf::Packet & packet)
{
	return socket_->send(packet) == sf::TcpSocket::Status::Done;
}
sf::Packet GameClient::receivePacket()
{
	sf::Packet packet;
	socket_->receive(packet);
	return packet;
}
void GameClient::waitForPlayerIndex()
{
	sf::Packet packet = receivePacket();
	player_idx_ = -1;
	packet >> player_idx_;
}
