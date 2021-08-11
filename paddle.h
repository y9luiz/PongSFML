#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <SFML/Graphics/Rect.hpp>
#include "movable.h"
#include <iostream>
class Paddle : public sf::RectangleShape, public Movable
{
	public:
		Paddle(const sf::Rect<float> & r);
		// top left point
		Paddle::Paddle(const float x, const float y, const float width, const float height);
		Paddle::Paddle(const float x, const float y, const  sf::Vector2f & size);
		~Paddle();
	protected:
		sf::Texture texture_;
		bool checkCollision(std::vector<std::shared_ptr<sf::Shape>>& shapes) override;

};