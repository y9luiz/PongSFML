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
void GameScreen::customizeButton()
{
	texture_.loadFromFile(ASSERTS_PATH + "/play_button.png");
	button_ = std::make_shared<Button>((WINDOW_WIDTH - 150) / 2, WINDOW_HEIGHT / 2 - 40, 150, 40, texture_);
}
void GameScreen::initScore()
{
	player1_score_ = 0;
	player2_score_ = 0;
	player1_win_ = 0;
	player2_win_ = 0;
	level_ = 0;

	if (!score_font_.loadFromFile(FONT_SCORE_PATH))
	{
		std::cout << "Erro ao tentar carregar a fonte. Path:" << FONT_SCORE_PATH << "\n";
	}
	score_board_.setFont(score_font_);
	score_board_.setCharacterSize(FONT_SCORE_SIZE);
	score_board_.setFillColor(FONT_SCORE_COLOR);
	win1_board_.setFont(score_font_);
	win1_board_.setCharacterSize(FONT_SCORE_SIZE - 4);
	win1_board_.setFillColor(FONT_SCORE_COLOR);
	win2_board_.setFont(score_font_);
	win2_board_.setCharacterSize(FONT_SCORE_SIZE - 4);
	win2_board_.setFillColor(FONT_SCORE_COLOR);
	displayScore(0, 0, 0, 0);
}

void displayScore(unsigned s1, unsigned s2, unsigned w1, unsigned w2) {
	score_board_.setString(std::to_string(s1) + " : " + std::to_string(s2));
	win1_board_.setString(std::to_string(w1));
	win2_board_.setString(std::to_string(w2));
	sf::FloatRect scoreBounds = score_board_.getLocalBounds(); //pega as delimitacoes do retangulo do texto
	score_board_.setOrigin(scoreBounds.left + scoreBounds.width / 2, scoreBounds.top + scoreBounds.height / 2);
	score_board_.setPosition(WINDOW_WIDTH / 2, 30);
	win1_board_.setPosition(20, 30);
	win2_board_.setPosition(60, 30);
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
						createObstacle();
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
		displayScore(player1_score_, player2_score_, player2_score_, player1_win_, player2_win_);
	}
	else if (pos.x>WINDOW_WIDTH)
	{
		obj->restartPosistion();
		player1_score_++;
		displayScore(player1_score_, player2_score_, player1_win_, player2_win_);
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
void GameScreen::checkEndLevel() {
	if(player1_score_ == 2) {
		level_++;
		player1_win_++;
		changeLevel();
	} else if(player2_score_ == 2) {
		level_++;
		player2_win_++;
		changeLevel();
	}
}
void GameScreen::changeLevel() {
	displayScore(player1_score_, player2_score_, player1_win_, player2_win_);

	if (level_ > 3) {
		level_ = 0;
	}

	ball_->setSpeed(ball_->getSpeed() + SPEED_INC);

	switch (level_)
	{
	case 0:
		createPlayScene();
	case 1:
		createLevel1Scene();
	case 2:
		/* code */
	case 3:
		createLevel3Scene();
		
	
	default:
		break;
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
void createLevel1Scene() {
	createPlayScene();
	createObstacle(std::make_shared<Paddle>(LEVEL1_OBST_RECT));
}
void createLevel2Scene(){
	createPlayScene();
}
void createLevel3Scene(){
	createPlayScene();
	createObstacle(std::make_shared<Paddle>(LEVEL3_OBST1_RECT));
	createObstacle(std::make_shared<Paddle>(LEVEL3_OBST2_RECT));
	
}
void GameScreen::createObstacle(std::shared_ptr<Paddle> ob) {
	ob->setFillColor(OBSTACLE_COLOR);
	scene_->addObject(ob);
	game_objects_.push_back(ob);
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
		checkEndLevel();

		std::this_thread::sleep_for(33ms);
	}
}
