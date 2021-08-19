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

	std::vector<std::shared_ptr<Screen>> screens; 
	screens.push_back(make_shared<MenuScreen>(WINDOW_WIDTH, WINDOW_HEIGHT, "Play"));
	screens.push_back(make_shared<GameScreen>(WINDOW_WIDTH, WINDOW_HEIGHT, "Play"));

	std::for_each(screens.begin(), screens.end(), [](std::shared_ptr<Screen> s)
		{
			s->setVisible(false);
		}
	);

	std::for_each(screens.begin(), screens.end(), [](std::shared_ptr<Screen> s)
		{
			s->setVisible(true);
			s->run();
		}
	);
	
	return 0;
}
