#include "game_screen.h"
#include <chrono>
#include <thread>
using namespace std::chrono_literals;

GameScreen::GameScreen(const int width, const int height, const std::string tittle) : Screen(width,height,tittle), tittle_(tittle)
{
	
	customizePlayer1();
	customizePlayer2();
	customizeBall();
	collider_.add(player1_);
	collider_.add(player2_);
	collider_.add(ball_);

}
void GameScreen::customizePlayer1()
{
	player1_ = std::make_shared<Paddle>(PLAYER_1_RECT);
	player1_->setFillColor(PLAYER_1_COLOR);
	player1_->setSpeed(PADDLE_SPEED);
}

void GameScreen::customizePlayer2()
{
	player2_ = std::make_shared<Paddle>(PLAYER_2_RECT);
	player2_->setFillColor(PLAYER_2_COLOR);
	player2_->setSpeed(PADDLE_SPEED);

}
void GameScreen::customizeBall()
{
	ball_ = std::make_shared<Ball>(BALL_INIT_POSITION, BALL_RADIUS);
	ball_->setFillColor(BALL_COLOR);
	ball_->setSpeed(BALL_SPEED);
}

void GameScreen::handleInput()
{
	while (pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			close();
		}
		if (event.KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Up)
			{
				player1_->moveUp();
			}
			else if (event.key.code == sf::Keyboard::Down)
			{
				player1_->moveDown();
			}
            if(event.key.code == sf::Keyboard::W)
            {
                player2_->moveUp();
            }
            else if(event.key.code == sf::Keyboard::S)
            {
                player2_->moveDown();
            }
		}
	}
};
void GameScreen::checkOutOfScreen(std::shared_ptr<Movable> & obj)
{
	sf::Vector2 pos = obj->getPosition();

	if(pos.x<0 || pos.y<0 || pos.x>WINDOW_WIDTH || pos.y>WINDOW_HEIGHT)
	{
		obj->restartPosistion();
	}
}

void GameScreen::run()
{
	auto objects = collider_.get();
	while (isOpen())
	{
		handleInput();
		clear(sf::Color::Black);
		autoMove(*ball_);
		
		ball_->checkCollision(objects);
		auto obj = std::dynamic_pointer_cast<Movable>(ball_);
		checkOutOfScreen(obj);
		// draw everything...
		for (auto& object : objects)
		{
			draw(*object);
		}
		
		
		display();
		std::this_thread::sleep_for(33ms);
	}
}
