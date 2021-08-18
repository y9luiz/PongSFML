#pragma once 
#include "screen.h"
#include "ball.h"
#include "paddle.h"
#include "defs.h"
#include "collider.h"

class GameScreen : public Screen
{
	public:
		GameScreen(const int width, const int height, const std::string tittle);
		void run() override;
	private:
		void customizePlayer1();
		void customizePlayer2();
		void customizeBall();
		void initScore();
		void displayScore(int s1, int s2);
		void handleInput() override;
		void checkOutOfScreen(std::shared_ptr<Movable> & obj);
		Collider collider_;
		std::string tittle_;
		std::shared_ptr<Ball> ball_;
		std::shared_ptr<Paddle> player1_;
		std::shared_ptr<Paddle> player2_;
        sf::Text score_board_;
		sf::Font score_font_;
		unsigned player1_score_;
		unsigned player2_score_;
};
