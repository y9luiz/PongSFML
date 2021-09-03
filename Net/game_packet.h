#pragma once
#include <SFML/Network.hpp>

class GamePacket : sf::Packet
{
	public:
		sf::Packet& operator >>(sf::Vector2f pos)
		{
			auto ptr = (sf::Packet*) this;
			*ptr >> pos.x;
			*ptr >> pos.y;
			return *this;
		}
		sf::Packet& operator << (sf::Vector2f pos)
		{
			auto ptr = (sf::Packet*)this;
			*ptr << pos.x;
			*ptr << pos.y;
			return *this;
		}
};