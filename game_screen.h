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
		friend void createMenuScene(GameScreen & game_screen);
		void customizePlayer1();
		void customizePlayer2();
		void customizeBall();
		std::shared_ptr<Button> customizeButton();
		void handleInput() override;
		void checkOutOfScreen(std::shared_ptr<Movable> & obj);
		std::string tittle_;
		std::shared_ptr<Ball> ball_;
		std::shared_ptr<Paddle> player1_;
		std::shared_ptr<Paddle> player2_;
		std::shared_ptr<Scene> scene_;
		std::shared_ptr<Button> button_;
		Scene::Type scene_type_;
};
