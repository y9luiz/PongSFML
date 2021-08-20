#include "game_screen.h"
#include <chrono>
#include <thread>
using namespace std::chrono_literals;

GameScreen::GameScreen(const int width, const int height, const std::string tittle) : Screen(width,height,tittle), tittle_(tittle)
{
	auto screen_ptr = dynamic_cast<Screen*>(this);

	scene_ = std::make_shared<Scene>(screen_ptr);
	createMenuScene();
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
void GameScreen::customizeButton()
{
	texture_.loadFromFile(ASSERTS_PATH+"/play_button.png");
	button_ = std::make_shared<Button>( (WINDOW_WIDTH - 150 )/2, WINDOW_HEIGHT/2-40, 150, 40, texture_);
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
			if( scene_type_ == Scene::Type::PLAY)
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
			else
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					auto ptr = getPtr(); // reference to this
					auto position = sf::Mouse::getPosition(*ptr);

					if (button_->isInside(position.x,position.y))
					{
						scene_type_ = Scene::Type::PLAY;
						createPlayScene();
					}
				}
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
void GameScreen::createMenuScene()
{
	scene_->clear();
	customizeButton();
	auto ptr = std::dynamic_pointer_cast<sf::Shape>(button_);
	scene_->addObject(button_);
}
void GameScreen::createPlayScene()
{
	scene_->clear();

	customizePlayer1();
	scene_->addObject(player1_);
	game_objects_.push_back(player1_);

	customizePlayer2();
	scene_->addObject(player2_);
	game_objects_.push_back(player2_);


	customizeBall();
	scene_->addObject(ball_);
	game_objects_.push_back(ball_);


}

void GameScreen::run()
{
	bool initialized_menu = true;
	while (isOpen())
	{
		if(scene_type_ == Scene::Type::PLAY)
		{
			autoMove(*ball_);
			ball_->checkCollision(game_objects_);
			auto obj = std::dynamic_pointer_cast<Movable>(ball_);
			checkOutOfScreen(obj);
		}
		else{
			if(!initialized_menu)
			{
				createMenuScene();
				initialized_menu = true;
			}
		}
		
		handleInput();
		scene_->drawObjects();
		display();

		std::this_thread::sleep_for(33ms);
	}
}
