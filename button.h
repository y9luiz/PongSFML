#pragma once
#include <SFML/Graphics.hpp>

class Button : public sf::Sprite
{
    public:
        Button(const int x, const int y, const int width, const int height, const sf::Texture& texture);
        Button(const int x, const int y, const int width, const int height);

    protected:
        std::shared_ptr<sf::Texture>  texture_;

};
