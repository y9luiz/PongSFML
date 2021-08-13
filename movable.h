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
			direction_x_y_.first = DirectionX::LEFT;

			direction_x_y_.second = DirectionY::UP;

			shape_ = shape_ptr;	
			shape_->setPosition(position);
			position_ = position;

		}
		Movable(sf::Shape * shape_ptr, const sf::Vector2f && position)
		{
			shape_ = shape_ptr;
			position_ = position;
			shape_->setPosition(position_);
		}
		inline void setSpeed(const sf::Vector2f& speed)
		{
			speed_ = speed;
			if (speed_.x > 0)
			{
				direction_x_y_.first = DirectionX::RIGHT;
			}
			else if(speed_.x < 0)
			{
				direction_x_y_.first = DirectionX::LEFT;
			}
			else
			{
				direction_x_y_.first = DirectionX::NONE;
			}

		}
		inline void setSpeed(sf::Vector2f&& speed)
		{
			speed_ = speed;
			speed.x = 0;
			speed.y = 0;
		}
		inline void moveRight()
		{
			direction_x_y_.first = DirectionX::RIGHT;
			position_.x += speed_.x;
			shape_->setPosition(position_);
		}
		inline void moveLeft()
		{
			direction_x_y_.first = DirectionX::LEFT;
			position_.x -= speed_.x;
			shape_->setPosition(position_);
		}
		inline void moveUp()
		{
			direction_x_y_.second = DirectionY::UP;
			position_.y -= speed_.y;
			shape_->setPosition(position_);
		}
		inline void moveDown()
		{
			direction_x_y_.second = DirectionY::DOWN;
			position_.y += speed_.y;
			shape_->setPosition(position_);
		}
		inline void moveByDirection()
		{
			if (direction_x_y_.first == DirectionX::LEFT)
			{
				moveLeft();
			}
			else if (direction_x_y_.first == DirectionX::RIGHT)
			{
				moveRight();
			}
			if (direction_x_y_.second == DirectionY::UP)
			{
				moveUp();
			}
			else if (direction_x_y_.second == DirectionY::DOWN)
			{
				moveDown();
			}
		}
		
		
	protected:
		sf::Shape* shape_;
		sf::Vector2f speed_;
		sf::Vector2f position_;
		virtual bool checkCollision(std::vector<std::shared_ptr<sf::Shape>> & shapes) = 0;

		enum class DirectionX {RIGHT,LEFT, NONE};
		enum class DirectionY { UP, DOWN, NONE};
		std::pair <DirectionX,DirectionY> direction_x_y_;


};