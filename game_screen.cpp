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
	this->paused = false;
	customizeBall();
	customizePlayer1();
	customizePlayer2();
	player1_score_ = 0;
	player2_score_ = 0;
	player1_win_ = 0;
	player2_win_ = 0;
	level_ = 0;
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
	button_ = std::make_shared<Button>((WINDOW_WIDTH - 100) / 2, WINDOW_HEIGHT / 2 - 40, 100, 40, texture_);
}

void GameScreen::initScore()
{
	if (!score_font_.loadFromFile(FONT_SCORE_PATH))
	{
		std::cout << "Erro ao tentar carregar a fonte. Path:" << FONT_SCORE_PATH << "\n";
	}
	score_board_ = std::make_shared<sf::Text>();
	score_board_->setFont(score_font_);
	score_board_->setCharacterSize(FONT_SCORE_SIZE);
	score_board_->setFillColor(FONT_SCORE_COLOR);

	win1_board_ = std::make_shared<sf::Text>();
	win1_board_->setFont(score_font_);
	win1_board_->setCharacterSize(FONT_SCORE_SIZE - 5);
	win1_board_->setFillColor(FONT_SCORE_COLOR);

	win2_board_ = std::make_shared<sf::Text>();
	win2_board_->setFont(score_font_);
	win2_board_->setCharacterSize(FONT_SCORE_SIZE - 5);
	win2_board_->setFillColor(FONT_SCORE_COLOR);

	displayScore(player1_score_, player1_score_, player1_win_, player2_win_);
}

void GameScreen::displayScore(unsigned s1, unsigned s2, unsigned w1, unsigned w2) {
	score_board_->setString(std::to_string(s1) + " : " + std::to_string(s2));
	win1_board_->setString(std::to_string(w1));
	win2_board_->setString(std::to_string(w2));

	sf::FloatRect scoreBounds = score_board_->getLocalBounds(); //pega as delimitacoes do retangulo do texto
	sf::FloatRect win1Bounds = win1_board_->getLocalBounds();
	sf::FloatRect win2Bounds = score_board_->getLocalBounds();

	score_board_->setOrigin(scoreBounds.left + scoreBounds.width / 2, scoreBounds.top + scoreBounds.height / 2);
	score_board_->setPosition(WINDOW_WIDTH / 2, 30);

	win1_board_->setPosition(WINDOW_WIDTH / 2 - scoreBounds.width / 2 - win1Bounds.width - 20, 15);
	win2_board_->setPosition(WINDOW_WIDTH / 2 + scoreBounds.width / 2 + 20, 15);
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
				//PAUSE GAME
				if (event.key.code == sf::Keyboard::Escape && this->paused == false)
				{
					pause();
					setSceneType(Scene::Type::PAUSE);
					createPauseScene();
				}
				if (event.key.code == sf::Keyboard::W && player1_->getPosition_().y - player1_->getSpeed().y >= 0)
				{
					player1_->moveUp();
				}
				else if (event.key.code == sf::Keyboard::S && player1_->getPosition_().y + player1_->getSpeed().y + PADDLE_SIZE.y <= WINDOW_HEIGHT)
				{
					player1_->moveDown();
				}
				if(event.key.code == sf::Keyboard::Up && player2_->getPosition_().y - player2_->getSpeed().y >= 0)
				{
					player2_->moveUp();
				}
				else if(event.key.code == sf::Keyboard::Down && player2_->getPosition_().y + player2_->getSpeed().y + PADDLE_SIZE.y <= WINDOW_HEIGHT)
				{
					player2_->moveDown();
				}
			}
			else if (scene_type_ == Scene::Type::PAUSE)
			{
				//RESUME GAME
				if (event.key.code == sf::Keyboard::F1 && this->paused == true)
				{
					setSceneType(Scene::Type::PLAY);
					scene_->removeObject(pause_text_);					
					unpause();
				}
				//MAIN MENU
				if (event.key.code == sf::Keyboard::F2 && this->paused == true)
				{
					setSceneType(Scene::Type::MENU);
					unpause();
					createMenuScene();
					player1_score_ = 0;
					player2_score_ = 0;
					player1_win_ = 0;
					player2_win_ = 0;
					level_ = 0;
				}
				//QUIT GAME
				if (event.key.code == sf::Keyboard::F3 && this->paused == true)
				{
					close();
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
}
void GameScreen::checkOutOfScreen(std::shared_ptr<Movable> & obj)
{
	sf::Vector2 pos = obj->getPosition_();

	if(pos.x < 0)
	{
		obj->restartPosistion();
		player2_score_++;
		displayScore(player1_score_, player2_score_, player1_win_, player2_win_);
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
	if(player1_score_ == 3) {
		player1_win_++;
		changeLevel();
	} else if(player2_score_ == 3) {
		player2_win_++;
		changeLevel();
	}
}
void GameScreen::changeLevel() {
	level_++;
	player1_score_ = 0;
	player2_score_ = 0;

	//sempre retornar pro level 0, porem velocidade continua aumentando
	if (level_ > 3) {
		level_ = 0;
	}

	//aumenta velocidade sempre que mudar de level
	sf::Vector2f speed = sf::Vector2f(ball_->getSpeed().x + SPEED_INCX, ball_->getSpeed().y + SPEED_INCY);
	ball_->setSpeed(speed);
	speed = sf::Vector2f(player1_->getSpeed().x, player1_->getSpeed().y + SPEED_INCP);
	player1_->setSpeed(speed);
	player2_->setSpeed(speed);

	switch (level_)
	{
	case 0:
		createPlayScene();
		break;
	case 1:
		createLevel1Scene();
		break;
	case 2:
		createLevel2Scene();
		break;
	case 3:
		createLevel3Scene();
		break;
	default:
		break;
	}

}

void GameScreen::createMenuScene()
{
	scene_->clear();
	game_objects_.clear();
	customizeButton();
	auto ptr = std::dynamic_pointer_cast<sf::Shape>(button_);
	scene_->addObject(button_);
}
void GameScreen::createPlayScene()
{
	scene_->clear();
	game_objects_.clear();

	scene_->addObject(player1_);
	game_objects_.push_back(player1_);

	scene_->addObject(player2_);
	game_objects_.push_back(player2_);

	scene_->addObject(ball_);
	game_objects_.push_back(ball_);

	initScore();
	scene_->addObject(score_board_);
	scene_->addObject(win1_board_);
	scene_->addObject(win2_board_);
}

void GameScreen::createPauseScene()
{
	//PAUSE MENU
	if (!pause_font_.loadFromFile(FONT_SCORE_PATH))
	{
		std::cout << "Erro ao tentar carregar a fonte. Path:" << FONT_PAUSE_PATH << "\n";
	}
	pause_text_ = std::make_shared<sf::Text>();
	pause_text_->setFont(pause_font_);
	pause_text_->setCharacterSize(FONT_PAUSE_SIZE);
	pause_text_->setFillColor(FONT_PAUSE_COLOR);

	//DISPLAY PAUSE
	pause_text_->setString("    PAUSED\n\nresume game\nmain menu\nquit");

	sf::FloatRect pause_bounds = pause_text_->getLocalBounds(); //pega as delimitacoes do retangulo do texto
	pause_text_->setOrigin(pause_bounds.left + pause_bounds.width / 2, pause_bounds.top + pause_bounds.height / 2);
	pause_text_->setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

	scene_->addObject(pause_text_);
}

void GameScreen::createLevel1Scene() {
	createPlayScene();
	createObstacle(std::make_shared<Paddle>(LEVEL1_OBST_RECT));
}
void GameScreen::createLevel2Scene() {
	createPlayScene();
	createObstacle(std::make_shared<Paddle>(LEVEL2_OBST1_RECT));
	createObstacle(std::make_shared<Paddle>(LEVEL2_OBST2_RECT));
}
void GameScreen::createLevel3Scene() {
	createPlayScene();
	createObstacle(std::make_shared<Paddle>(LEVEL3_OBST1_RECT));
	createObstacle(std::make_shared<Paddle>(LEVEL3_OBST2_RECT));
}
void GameScreen::createObstacle(std::shared_ptr<Paddle> obstacle) {
	obstacle->setFillColor(OBSTACLE_COLOR);
	scene_->addObject(obstacle);
	game_objects_.push_back(obstacle);
}

void GameScreen::run()
{
	bool initialized_menu = true;
	while (isOpen())
	{
		if (scene_type_ == Scene::Type::PLAY)
		{
			autoMove(*ball_);
			ball_->checkCollision(game_objects_);
			auto obj = std::dynamic_pointer_cast<Movable>(ball_);
			checkOutOfScreen(obj);
		}
		else if (scene_type_ == Scene::Type::PAUSE)
		{
			
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
   		checkEndLevel();
    
		std::this_thread::sleep_for(33ms);
	}
}
