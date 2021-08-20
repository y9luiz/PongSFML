#include "game_screen.h"
#include <chrono>
#include <thread>
using namespace std::chrono_literals;

GameScreen::GameScreen(const int width, const int height, const std::string tittle) : Screen(width,height,tittle), tittle_(tittle)
{
	auto ptr = dynamic_cast<Screen*>(this);

	customizePlayer1();
	customizePlayer2();
	customizeBall();
	scene_ = std::make_shared<Scene>(ptr);

	scene_->addObject(player1_);
	scene_->addObject(player2_);
	scene_->addObject(ball_);
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
std::shared_ptr<Button> customizeButton()
{
	sf::Texture texture;
	auto button = std::make_shared<Button>(75,150,150,40,texture);
	return button;
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
void createMenuScene(GameScreen & game_screen)
{
	game_screen.scene_->addObject( std::dynamic_pointer_cast<sf::Shape>(customizeButton()));
}

void GameScreen::run()
{
	auto objects = scene_->getObjects();
	while (isOpen())
	{
		
		handleInput();
		clear(sf::Color::Black);
		autoMove(*ball_);
		
		ball_->checkCollision(objects);
		auto obj = std::dynamic_pointer_cast<Movable>(ball_);
		checkOutOfScreen(obj);
		// draw everything...
		scene_->drawObjects();
		
		display();
		std::this_thread::sleep_for(33ms);
	}
}
