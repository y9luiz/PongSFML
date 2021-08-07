#include "paddle.h"

Paddle::Paddle() : sf::RectangleShape()
{

}
Paddle::Paddle(const sf::Rect<float> & r) : sf::RectangleShape()
{
	Paddle::geometric_shape_ = r;
	sf::Vector2f size(r.width, r.height);
	this->setSize(size);
	this->setPosition(r.left, r.top);
}
Paddle::Paddle(const float x, const float y, const  sf::Vector2f& size) : sf::RectangleShape(size)
{
	this->setPosition(sf::Vector2f(x, y));
}
Paddle::Paddle(const float x, const float y, const float width, const float height) : 
	sf::RectangleShape(sf::Vector2f (x,y))
{
	sf::Vector2f size(width, height);
	this->setSize(size);
}

Paddle::~Paddle()
{
	
}
bool Paddle::checkCollision(sf::Rect<float> & geometric_shape)
{
	return Paddle::geometric_shape_.intersects(geometric_shape);
}
bool Paddle::checkCollision(float x, float y)
{
	return geometric_shape_.contains(sf::Vector2f(x,y));
}
