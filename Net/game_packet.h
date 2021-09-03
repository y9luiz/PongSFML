#pragma once
#include <SFML/Network.hpp>

class GamePacket : public sf::Packet
{
	public:

		sf::Packet& operator >>(sf::Vector2f & pos)
		{
			auto ptr = (sf::Packet*) this;
			*ptr >> pos.x;
			*ptr >> pos.y;
			return *this;
		}
		sf::Packet& operator << ( const sf::Vector2f & pos)
		{
			auto ptr = (sf::Packet*)this;
			*ptr << pos.x;
			*ptr << pos.y;
			return *this;
		}
		sf::Packet & operator<<(bool v)
		{
			return sf::Packet::operator<<(v);
		}
};