#include "paddle.h"

Paddle::Paddle(const sf::Rect<float> & r) : sf::RectangleShape(),
		Movable(dynamic_cast<sf::Shape*> (this), sf::Vector2f(r.left, r.top))
{
	sf::Vector2f size(r.width, r.height);
	this->setSize(size);
}
Paddle::Paddle(const float x, const float y, const  sf::Vector2f& size) : 
	sf::RectangleShape(size),
	Movable(dynamic_cast<sf::Shape*> (this), sf::Vector2f(x, y))
{
}
Paddle::Paddle(const float x, const float y, const float width, const float height) : 
	sf::RectangleShape(sf::Vector2f (x,y)), 
	Movable(dynamic_cast<sf::Shape*> (this), sf::Vector2f(x, y))
{
	sf::Vector2f size(width, height);
	this->setSize(size);
}

Paddle::~Paddle()
{
	
}

bool Paddle::checkCollision(std::vector<std::shared_ptr<sf::Shape>>& shapes)
{
	auto tgt_bound = this->getGlobalBounds();

	for (const auto & shape : shapes)
	{
		if (shape.get() != (this))
		{
			auto src_bound = shape->getGlobalBounds();
			if (tgt_bound.intersects(src_bound))
			{
				return true;
			}
		}
	}
	return false;
}
