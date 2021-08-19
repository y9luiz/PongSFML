#include "menu_screen.h"
#include <thread>
#include <chrono>
#include "defs.h"
using namespace std::chrono_literals;

MenuScreen::MenuScreen(const int width, const int height, const std::string tittle)  : Screen(width, height, tittle), tittle_(tittle)
{
}

void MenuScreen::run()
{
	is_running_ = true;
	texture_.loadFromFile("Assets/play_button.png");
	setButton( (WINDOW_WIDTH - 150 )/2, WINDOW_HEIGHT/2-40, 150, 40, texture_);
	
	while (isOpen() && is_running_)
	{
		clear(sf::Color::Black);
		draw(*play_button_);
		display();
		handleInput();
		std::this_thread::sleep_for(33ms);
	}
}

void MenuScreen::handleInput()
{
	while (pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			close();
		}
		if (event.KeyPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				MenuScreen* ptr = static_cast<MenuScreen*>(this);
				auto position = sf::Mouse::getPosition(*ptr);

				if (play_button_->isInside(position.x,position.y))
				{
					ptr->is_running_ = false;
				}
			}
			
		}
	}
}