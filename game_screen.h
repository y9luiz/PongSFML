#pragma once 
#include "screen.h"
#include "ball.h"
#include "paddle.h"
#include "defs.h"
#include "collider.h"
#include "scene.h"
#include "button.h"
#include "Net/net.h"
#include <unordered_map>
#include <memory>


class ScoreBoard
{
	public:
		unsigned player1_score_;
		unsigned player2_score_;
		unsigned player1_win_;
		unsigned player2_win_;
		std::shared_ptr<sf::Text> score_view_;

		std::string toString()
		{
			auto player1_score = std::to_string(player1_score_);
			auto player2_score = std::to_string(player2_score_);
			auto player1_win = std::to_string(player1_win_);
			auto player2_win = std::to_string(player2_win_);

			const char sep = ';';  // separator
			
			return player1_score + sep + player2_score + sep + player1_win + sep +  player2_win;
		}

};

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
		static inline void createClient(const std::string& server_address)
		{
			client_ = std::make_shared<GameClient>(server_address);
		}
		static std::shared_ptr<GameClient> client_;

	protected:
		bool paused;

	private:
		GameScreen(const int width, const int height, const std::string tittle);
		void createMenuScene();
		void createPlayScene();
		void createPauseScene();
		void createLevel1Scene();
		void createLevel2Scene();
		void createLevel3Scene();
		void customizePlayer1();
		void customizePlayer2();
		void customizeBall();
		void customizeButtons();
		void initScore();
		void displayScore(unsigned s1, unsigned s2, unsigned w1, unsigned w2);
		void createObstacle(std::shared_ptr<Paddle> ob);
		void checkEndLevel();
		void changeLevel();
		void handleInput() override;
		void checkOutOfScreen(std::shared_ptr<Movable> & obj);
		inline void pause() { this->paused = true; }
		inline void unpause() { this->paused = false; }
		
		std::string tittle_;
		std::shared_ptr<Ball> ball_;
		std::shared_ptr<Paddle> player1_;
		std::shared_ptr<Paddle> player2_;
		//std::shared_ptr<Paddle> obstacle1_;
		//std::shared_ptr<Paddle> obstacle2_;
		std::shared_ptr<Scene> scene_;
		std::unordered_map<std::string,std::shared_ptr<Button>> buttons_;
		sf::Texture texture_;
		Scene::Type scene_type_;
		std::vector<std::shared_ptr<sf::Shape>> game_objects_;
		std::shared_ptr<sf::Text> win1_board_;
		std::shared_ptr<sf::Text> win2_board_;
		std::shared_ptr<sf::Text> pause_text_;
		sf::Font score_font_;
		sf::Font pause_font_;
		sf::Font menu_font_;
		ScoreBoard score_board_;
		unsigned level_;
		HostType host_type_;
};