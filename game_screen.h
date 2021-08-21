#pragma once 
#include "screen.h"
#include "ball.h"
#include "paddle.h"
#include "defs.h"
#include "collider.h"
#include "scene.h"
#include "button.h"
#include <memory>

class GameScreen : public Screen, public std::enable_shared_from_this<GameScreen>
{
	public:
	
		void run() override;
        static inline std::shared_ptr<GameScreen> create( const int width, const int height, 
				const std::string tittle)
        {
			
			return std::shared_ptr<GameScreen>(new GameScreen(width,height,tittle));

        }
        std::shared_ptr<GameScreen> getPtr(){return shared_from_this();};
		inline void setSceneType(Scene::Type scene_type)
		{
			scene_type_ = scene_type;
		}
	private:
		GameScreen(const int width, const int height, const std::string tittle);
		void createMenuScene();
		void createPlayScene();
		void createLevel1Scene();
		void createLevel2Scene();
		void createLevel3Scene();
		void customizePlayer1();
		void customizePlayer2();
		void customizeBall();
		void customizeButton();
		void initScore();
		void displayScore(unsigned s1, unsigned s2, unsigned w1, unsigned w2);
		void createObstacle();
		void checkEndLevel();
		void handleInput() override;
		void checkOutOfScreen(std::shared_ptr<Movable> & obj);
		std::string tittle_;
		std::shared_ptr<Ball> ball_;
		std::shared_ptr<Paddle> player1_;
		std::shared_ptr<Paddle> player2_;
		//std::shared_ptr<Paddle> obstacle1_;
		//std::shared_ptr<Paddle> obstacle2_;
		std::shared_ptr<Scene> scene_;
		std::shared_ptr<Button> button_;
		sf::Texture texture_;
		Scene::Type scene_type_;
		std::vector<std::shared_ptr<sf::Shape>> game_objects_;
		sf::Text score_board_;
		sf::Font score_font_;
		sf::Text win1_board_;
		sf::Text win2_board_;
		unsigned player1_score_;
		unsigned player2_score_;
		unsigned player1_win_;
		unsigned player2_win_;
		unsigned level_;
};