#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
class Collider
{
	typedef std::vector<std::shared_ptr<sf::Shape>>::iterator iterator;

	public:

		Collider()
		{

		}
		iterator  begin()
		{
			return shapes_.begin();
		}
		iterator  end()
		{
			return shapes_.end();
		}
		void add(std::shared_ptr<sf::Shape> & shape)
		{	
			shapes_.push_back(shape);
		}
		void add(std::shared_ptr<sf::Shape> && shape)
		{
			shapes_.push_back(shape);
			shape.reset();
		}

		bool checkCollision(std::shared_ptr<sf::Shape> object)
		{
			auto tgt_bound = object->getGlobalBounds();

			for (const auto & shape : shapes_)
			{
				if (shape != object)
				{
					auto src_bound = shape->getGlobalBounds();
					
					if (tgt_bound.intersects(src_bound))
					{
						return true;
					}
				}
			}
			return false;
		}
		std::vector<std::shared_ptr<sf::Shape>> get() {
			return shapes_;
		}
	protected:
		std::vector<std::shared_ptr<sf::Shape>> shapes_;
		
};