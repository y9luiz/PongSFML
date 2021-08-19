// SFMLPong.cpp : Defines the entry point for the application.
//

#include <chrono>
#include <thread>

#include "SFMLPong.h"
#include "screen.h"
#include "game_screen.h"
#include "menu_screen.h"

using namespace std;
using namespace chrono_literals;

int main()
{
	std::shared_ptr<Screen> screen_ptr = make_shared<MenuScreen>(WINDOW_WIDTH, WINDOW_HEIGHT, "Play");
	screen_ptr->run();
	screen_ptr = make_shared<GameScreen>(WINDOW_WIDTH, WINDOW_HEIGHT, "Play");
	screen_ptr->run();

	return 0;
}
