// SFMLPong.cpp : Defines the entry point for the application.
//

#include "SFMLPong.h"
#include <SFML/Graphics.hpp>
#include "paddle.h"
#include "ball.h"
#include "collider.h"

using namespace std;

int main()
{
	Collider c;

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pong");

	std::shared_ptr<Paddle> player1 = std::make_shared<Paddle>(PLAYER_1_RECT);
	std::shared_ptr<Paddle> player2 = std::make_shared<Paddle>(PLAYER_2_RECT);
	std::shared_ptr <Ball> ball = std::make_shared<Ball>(BALL_INIT_POSITION,BALL_RADIUS);
	
	c.add(player1);
	c.add(player2);
	c.add(ball);

	player1->setFillColor(sf::Color(150, 0, 0));
	player1->setSpeed(PADDLE_SPEED);
	player2->setFillColor(sf::Color(0, 0, 150));
	ball->setFillColor(sf::Color(0, 0, 150));
	
	sf::Event event;

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
					player1->moveUp();
				}
				else if (event.key.code == sf::Keyboard::Down)
				{
					player1->moveDown();
				}
			}
			
		}
	
		// clear the window with black color
		window.clear(sf::Color::Black);

		// draw everything here...

		for (const auto& shape : c)
		{
			window.draw(*shape);
			c.checkCollision(shape);
		}
	  
		// end the current frame
		window.display();
	}

	return 0;
}
