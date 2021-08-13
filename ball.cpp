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
bool Ball::checkCollision(std::vector<std::shared_ptr<sf::Shape>>& shapes)
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
void Ball::autoMove()
{
	auto change_direction_x = [&]()
	{
		if (direction_x_y_.first == DirectionX::LEFT)
		{
			direction_x_y_.first = DirectionX::RIGHT;
		}
		else
		{
			direction_x_y_.first = DirectionX::LEFT;
		}
	};
	auto change_direction_y = [&]()
	{
		std::uniform_int_distribution<int> distribution(0, 1);
		int direction = distribution(generator);
		switch (direction)
		{
			case 0:
				direction_x_y_.second = DirectionY::UP;
				break;
			case 1:
				direction_x_y_.second = DirectionY::DOWN;
			default:
				break;
		}
		
	};
	if (position_.x < 0)
	{
		restartPosistion();
	}
	if (!collided_)
	{
		moveByDirection();
	}
	else 
	{
		change_direction_x();
		change_direction_y();
		collided_ = false;
		autoMove();
	}
}