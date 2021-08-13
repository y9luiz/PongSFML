#include "ball.h"

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
		if (direction_x_y_.second == DirectionY::UP)
		{
			direction_x_y_.second = DirectionY::DOWN;
		}
		else
		{
			direction_x_y_.second = DirectionY::UP;
		}
	};
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