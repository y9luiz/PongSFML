#pragma once
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics.hpp>

#include <SFML/System/Vector2.hpp>
#include "solid_object.h"
#include "circle.h"
//Game Object
class Ball : public sf::CircleShape, public SolidObject<Circle>
{
	public:
		Ball();
		Ball(const Circle &  c);
		Ball(const  sf::Vector2f& center, const float radius);
		Ball(const float x, const float y, const float radius);
		~Ball();
protected:
	sf::Texture texture_;
	bool checkCollision(Circle & geometric_shape) override;
	bool checkCollision(float x, float y) override;
};