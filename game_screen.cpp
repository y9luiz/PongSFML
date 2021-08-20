#include "game_screen.h"
#include <chrono>
#include <thread>
#include <iostream>
#include<string>
using namespace std::chrono_literals;

GameScreen::GameScreen(const int width, const int height, const std::string tittle) : Screen(width,height,tittle), tittle_(tittle)
{
	
	auto screen_ptr = dynamic_cast<Screen*>(this);

	scene_ = std::make_shared<Scene>(screen_ptr);
	createMenuScene();
	initScore();


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
void GameScreen::initScore()
{
	player1_score_ = 0;
	player2_score_ = 0;

	if (!score_font_.loadFromFile(FONT_SCORE_PATH))
	{
		std::cout << "Erro ao tentar carregar a fonte. Path:" << FONT_SCORE_PATH << "\n";
	}
	score_board_.setFont(score_font_);
	score_board_.setCharacterSize(FONT_SCORE_SIZE);
	score_board_.setFillColor(FONT_SCORE_COLOR);
	displayScore(0, 0);
}

void GameScreen::displayScore(int s1, int s2) {
	score_board_.setString(std::to_string(s1) + " : " + std::to_string(s2));

	sf::FloatRect scoreBounds = score_board_.getLocalBounds(); //pega as delimitacoes do retangulo do texto
	score_board_.setOrigin(scoreBounds.left + scoreBounds.width / 2, scoreBounds.top + scoreBounds.height / 2);
	score_board_.setPosition(WINDOW_WIDTH / 2, 30);
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
	sf::Vector2 pos = obj->getPosition_();

	if(pos.x < 0)
	{
		obj->restartPosistion();
		player2_score_++;
		displayScore(player1_score_, player2_score_);
	}
	else if (pos.x>WINDOW_WIDTH)
	{
		obj->restartPosistion();
		player1_score_++;
		displayScore(player1_score_, player2_score_);
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
		draw(score_board_);
		display();

		std::this_thread::sleep_for(33ms);
	}
}
