#pragma once
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics.hpp>

#include <SFML/System/Vector2.hpp>
#include "circle.h"
#include "movable.h"
//Game Object
class Ball : public sf::CircleShape, public Movable
{
	public:
		Ball(const Circle &  c);
		Ball(const  sf::Vector2f& center, const float radius);
		Ball(const float x, const float y, const float radius);
		~Ball();
		bool checkCollision(std::vector<std::shared_ptr<sf::Shape>>& shapes) override;
		void autoMove();

	protected:
		sf::Texture texture_;
		bool collided_;
};