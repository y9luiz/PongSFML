#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <SFML/Graphics/Rect.hpp>
#include "solid_object.h"
#include <iostream>
class Paddle : public sf::RectangleShape, public SolidObject<sf::Rect<float>>
{
	public:
		Paddle();
		Paddle(const sf::Rect<float> & r);
		// top left point
		Paddle::Paddle(const float x, const float y, const float width, const float height);
		Paddle::Paddle(const float x, const float y, const  sf::Vector2f & size);
		~Paddle();
		inline void moveUp()
		{
			SolidObject::moveUp();
			sf::Rect<float> r = SolidObject::geometric_shape_;
			this->setPosition(sf::Vector2f(r.left, r.top));
		}
		inline void moveDown()
		{
			SolidObject::moveDown();
			sf::Rect<float> r = SolidObject::geometric_shape_ ;
			this->setPosition(sf::Vector2f(r.left,r.top));
		}
	protected:
		sf::Texture texture_;
		bool checkCollision(sf::Rect<float> & geometric_shape) override;
		bool checkCollision(float x, float y) override;
		
};