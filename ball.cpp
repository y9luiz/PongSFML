#include "ball.h"
#include <chrono>
#include <iostream>

const int seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine Ball::generator(seed);

Ball::Ball(const Circle& c) :
	CircleShape(c.getRadius()),
	Movable(dynamic_cast<sf::Shape*>(this), sf::Vector2f(c.getX(), c.getY()))
{

}
Ball::Ball(const sf::Vector2f& center, const float radius) :
	CircleShape(radius),
	Movable(dynamic_cast<sf::Shape*>(this), center)
{
}
Ball::Ball(const float x, const float y, const float radius) :
	CircleShape(radius),
	Movable(dynamic_cast<sf::Shape*>(this), sf::Vector2(x, y))
{
}
Ball::~Ball()
{

}
bool Ball::checkCollision(std::vector<std::shared_ptr<sf::Shape>> & shapes)
{
	auto tgt_bound = this->getGlobalBounds();

	for (const auto& shape : shapes)
	{
		if (shape.get() != (this))
		{
			auto src_bound = shape->getGlobalBounds();
			if (tgt_bound.intersects(src_bound))
			{
				collided_ = true;
				return true;
			}
		}
	}
	collided_ = false;
	return false;
}
void autoMove(Ball & ball)
{
	auto change_direction_x = [&]()
	{
		if (ball.direction_x_y_.first == ball.DirectionX::LEFT)
		{
			ball.direction_x_y_.first = ball.DirectionX::RIGHT;
		}
		else
		{
			ball.direction_x_y_.first = ball.DirectionX::LEFT;
		}
	};
	auto change_direction_y = [&]()
	{
		std::uniform_int_distribution<int> distribution(0, 1);
		int direction = distribution(ball.generator);
		switch (direction)
		{
			case 0:
				ball.direction_x_y_.second = ball.DirectionY::UP;
				break;
			case 1:
				ball.direction_x_y_.second = ball.DirectionY::DOWN;
			default:
				break;
		}
		
	};
	if (ball.position_.x < 0)
	{
		ball. restartPosistion();
	}
	if (!ball.collided_)
	{
		ball.moveByDirection();
	}
	else 
	{
		change_direction_x();
		change_direction_y();
		ball.collided_ = false;
		// to avoid "enter inside other objects"
		ball.moveByDirection();
	}
}
