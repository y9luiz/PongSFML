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
			if (event.key.code == sf::Keyboard::Up and player1_->getPosition_().y - player1_->getSpeed().y >= 0)
			{
				player1_->moveUp();
			}
			else if (event.key.code == sf::Keyboard::Down and player1_->getPosition_().y + player1_->getSpeed().y + PADDLE_SIZE.y <= WINDOW_HEIGHT)
			{
				player1_->moveDown();
			}

			if (event.key.code == sf::Keyboard::W and player2_->getPosition_().y - player2_->getSpeed().y >= 0)
			{
				player2_->moveUp();
			}
			else if (event.key.code == sf::Keyboard::S and player2_->getPosition_().y + player2_->getSpeed().y + PADDLE_SIZE.y <= WINDOW_HEIGHT)
			{
				player2_->moveDown();
			}
		}
	}
};
void GameScreen::checkOutOfScreen(std::shared_ptr<Movable> & obj)
{
	sf::Vector2 pos = obj->getPosition_();

	if(pos.x < 0)
	{
		obj->restartPosistion();
		//todo: contar ponto pro player2
	}
	else if (pos.x>WINDOW_WIDTH)
	{
		obj->restartPosistion();
		//todo: contar ponto pro player1
	}

	if(pos.y <= 0)
	{
		obj->changeDirectionToDown();
	}
	else if(pos.y + 2 * BALL_RADIUS >= WINDOW_HEIGHT)
	{
		obj->changeDirectionToUp();
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
