#pragma once
#include <SFML/System/Vector2.hpp>
#include <math.h>
class Circle
{
	public:
		Circle()
		{
			radius_ = 0;
			center_.x = 0;
			center_.y = 0;
		};
		Circle(const sf::Vector2f & point, const float radius)
		{
			center_ = point;
			radius_ = radius;
		};
		Circle(const float x, const float y, const float radius)
		{
			center_.x = x;
			center_.y = y;
			radius_ = radius;
		};
		inline bool contains(const sf::Vector2f & point) const
		{
			return sqrt(pow(point.x - center_.x, 2) + pow(point.y - center_.y, 2)) < radius_;
		};
		inline void setRadius(const float radius)
		{
			radius_ = radius;
		};
		inline void setX(const float x)
		{
			center_.x = x;
		};
		inline void setY(const float y)
		{
			center_.y = y;
		};
		inline float getRadius() const
		{
			return radius_;
		};
		inline float getX() const
		{
			return center_.x;
		};
		inline float getY() const
		{
			return center_.y;
		};

	protected:
		float radius_;
		sf::Vector2f center_;
};