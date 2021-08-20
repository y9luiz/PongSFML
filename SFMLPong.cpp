// SFMLPong.cpp : Defines the entry point for the application.
//

#include <chrono>
#include <thread>

#include "SFMLPong.h"
#include "screen.h"
#include "game_screen.h"
#include "scene.h"
using namespace std;
using namespace chrono_literals;

int main()
{
	std::shared_ptr<GameScreen> screen = GameScreen::create(WINDOW_WIDTH, WINDOW_HEIGHT, "Play");

	screen->run();
		
	return 0;
}
