#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <functional>

class Movable
{
	public:
		Movable()
		{

		}
		Movable(sf::Shape * shape_ptr, const sf::Vector2f& position)
		{
			shape_ = shape_ptr;	
			shape_->setPosition(position);
			position_ = position;
		}
		Movable(sf::Shape* shape_ptr, const sf::Vector2f && position)
		{
			shape_ = shape_ptr;
			position_ = position;
			shape_->setPosition(position_);

		}
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
			position_.y -= speed_.y;
			shape_->setPosition(position_);
		}
		inline void moveDown()
		{
			position_.y += speed_.y;
			shape_->setPosition(position_);
		}
		inline void moveRight()
		{
			position_.x += speed_.x;
			shape_->setPosition(position_);
		}
		inline void moveLeft()
		{
			position_.x -= speed_.x;
			shape_->setPosition(position_);
		}
		
	protected:
		sf::Shape* shape_;
		sf::Vector2f speed_;
		sf::Vector2f position_;
		virtual bool checkCollision(std::vector<std::shared_ptr<sf::Shape>> & shapes) = 0;
};