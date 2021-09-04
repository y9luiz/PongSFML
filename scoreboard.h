#pragma once
#include <string>
#include <SFML/Graphics/Text.hpp>
class ScoreBoard
{
public:

	std::string toString()
	{
		auto player1_score_str = std::to_string(player1_score);
		auto player2_score_str = std::to_string(player2_score);
		auto player1_win_str = std::to_string(player1_win);
		auto player2_win_str = std::to_string(player2_win);

		const char sep = ';';  // separator

		return player1_score_str + sep + player2_score_str + sep + 
			player1_win_str + sep + player2_win_str;
	}
	unsigned player1_score = 0;
	unsigned player2_score = 0;
	unsigned player1_win = 0;
	unsigned player2_win = 0;
	std::shared_ptr<sf::Text> score_view;

};