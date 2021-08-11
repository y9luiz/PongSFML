#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
void hello(std::shared_ptr<sf::Shape> s)
{

}
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

		void checkCollision(std::shared_ptr<sf::Shape> object)
		{
			auto tgt_bound = object->getGlobalBounds();

			for (const auto & shape : shapes_)
			{
				if (shape != object)
				{
					auto src_bound = shape->getGlobalBounds();
					
					if (tgt_bound.intersects(src_bound))
					{
						std::cout << "colidiu\n";
					}
				}
			}
		}
	protected:
		std::vector<std::shared_ptr<sf::Shape>> shapes_;
		
};