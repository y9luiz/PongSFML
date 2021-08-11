#include "ball.h"

Ball::Ball(const Circle & c):
CircleShape(c.getRadius()),
	Movable(dynamic_cast<sf::Shape*>(this), sf::Vector2f(c.getX(),c.getY()))
{

}
Ball::Ball(const sf::Vector2f& center, const float radius) : 
  CircleShape(radius),
  Movable(dynamic_cast<sf::Shape*>(this), center)
{
}
Ball::Ball(const float x, const float y, const float radius) : 
	CircleShape(radius),
	Movable( dynamic_cast<sf::Shape*>(this),sf::Vector2(x,y))
{
}
Ball::~Ball()
{

}
bool Ball::checkCollision(std::vector<std::shared_ptr<sf::Shape>>& shapes) 
{
	return false;
}
