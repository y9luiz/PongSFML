// SFMLPong.cpp : Defines the entry point for the application.
//

#include "SFMLPong.h"
#include <SFML/Graphics.hpp>
#include "paddle.h"
#include "ball.h"
using namespace std;



int main()
{

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pong");

	sf::Event event;

	Paddle p1(PLAYER_1_RECT),p2(PLAYER_2_RECT);

	Ball ball(BALL_INIT_POSITION,BALL_RADIUS);

	p1.setFillColor(sf::Color(150, 0, 0));
	p2.setFillColor(sf::Color(0, 0, 150));
	p1.setSpeed(PADDLE_SPEED);
	ball.setFillColor(sf::Color(0, 0, 150));

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (event.KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Up)
				{
					p1.moveUp();
				}
				else if (event.key.code == sf::Keyboard::Down)
				{
					p1.moveDown();
				}
			}
			
		}
	
		// clear the window with black color
		window.clear(sf::Color::Black);

		// draw everything here...
	   // window.draw(...);
		
		window.draw(p1);
		window.draw(p2);
		window.draw(ball);

		// end the current frame
		window.display();
	}

	return 0;
}
