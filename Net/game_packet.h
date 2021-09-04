#pragma once
#include <SFML/Network.hpp>
#include "../scoreboard.h"
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
		
		sf::Packet& operator << (const ScoreBoard & scoreboard)
		{
			auto ptr = (sf::Packet*)this;
			*ptr << scoreboard.player1_score;
			*ptr << scoreboard.player1_win;
			*ptr << scoreboard.player2_score;
			*ptr << scoreboard.player2_win;

			return *this;
		}
		sf::Packet& operator >> (ScoreBoard& scoreboard)
		{
			auto ptr = (sf::Packet*)this;
			*ptr >> scoreboard.player1_score;
			*ptr >> scoreboard.player1_win;
			*ptr >> scoreboard.player2_score;
			*ptr >> scoreboard.player2_win;

			return *this;
		}
		sf::Packet & operator<<(bool v)
		{
			return sf::Packet::operator<<(v);
		}

};