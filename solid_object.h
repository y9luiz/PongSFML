#pragma once
#include <iostream>

template <class T>
class SolidObject
{
	public:
		inline void setSpeed(const sf::Vector2f& speed)
		{
			speed_ = speed;
		}
		inline void setSpeed(sf::Vector2f&& speed)
		{
			speed_ = speed;
			speed.x = 0;
			speed.y = 0;
		}
		inline void moveUp()
		{
			geometric_shape_.top -= speed_.y;
		}
		inline void moveDown()
		{
			geometric_shape_.top += speed_.y;
		}
	protected:
		T geometric_shape_;
		sf::Vector2f speed_;
		virtual bool checkCollision(T & geometric_shape) = 0;
		virtual bool checkCollision(float x, float y) = 0;

		
};