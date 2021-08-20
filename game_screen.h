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
	protected:
		bool paused;

	private:
		GameScreen(const int width, const int height, const std::string tittle);
		void createMenuScene();
		void createPlayScene();
		void customizePlayer1();
		void customizePlayer2();
		void customizeBall();
		void customizeButton();
		void initScore();
		void displayScore(int s1, int s2);
		void handleInput() override;
		void checkOutOfScreen(std::shared_ptr<Movable> & obj);
		inline void pause() { this->paused = true; }
		inline void unpause() { this->paused = false; }
		void pause_menu();
		void display_pause();
		std::string tittle_;
		std::shared_ptr<Ball> ball_;
		std::shared_ptr<Paddle> player1_;
		std::shared_ptr<Paddle> player2_;
		std::shared_ptr<Scene> scene_;
		std::shared_ptr<Button> button_;
		sf::Texture texture_;
		Scene::Type scene_type_;
		std::vector<std::shared_ptr<sf::Shape>> game_objects_;
		sf::Text score_board_;
		sf::Font score_font_;
		unsigned player1_score_;
		unsigned player2_score_;
		sf::Text pause_text_;
		sf::Font pause_font_;
};