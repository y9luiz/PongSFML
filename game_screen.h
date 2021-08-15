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

		void handleInput() override;
		Collider collider_;
		std::string tittle_;
		std::shared_ptr<Ball> ball_;
		std::shared_ptr<Paddle> player1_;
		std::shared_ptr<Paddle> player2_;
};