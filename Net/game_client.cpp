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
	return status == sf::TcpSocket::Done;
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