#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <SFML/Graphics/Rect.hpp>
#include "solid_object.h"
class Paddle : public sf::RectangleShape, SolidObject<sf::Rect<float>>
{
	public:
		Paddle();
		Paddle(const sf::Rect<float> & r);
		// top left point
		Paddle::Paddle(const float x, const float y, const float width, const float height);
		Paddle::Paddle(const float x, const float y, const  sf::Vector2f & size);
		~Paddle();
	protected:
		sf::Texture texture_;
		bool checkCollision(sf::Rect<float> & geometric_shape) override;
		bool checkCollision(float x, float y) override;
};