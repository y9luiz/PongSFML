#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
class Screen : public sf::RenderWindow 
{
	public:
		Screen(const int width, const int height, std::string tittle)
			: RenderWindow(sf::VideoMode(width, height),tittle), tittle_(tittle){}
		virtual void handleInput() = 0;
		virtual void run() = 0;
		inline void setClock(sf::Clock & clock)
		{
			clock_ = clock;
		}
		
	protected:
		const std::string tittle_;
		sf::Clock clock_;
		sf::Event event;
};
