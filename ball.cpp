#include "ball.h"
Ball::Ball()
{

}
Ball::Ball(const Circle & c)
{

}
Ball::Ball(const  sf::Vector2f& center, const float radius) : CircleShape(radius)
{
	setPosition(center);
}
Ball::Ball(const float x, const float y, const float radius) : CircleShape(radius)
{
	setPosition(x,y);
}
Ball::~Ball()
{

}
bool Ball::checkCollision(Circle & geometric_shape)
{
	return false;
}
bool Ball::checkCollision(float x, float y)
{
	return false;
}
