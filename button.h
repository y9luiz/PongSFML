#pragma once
#include <SFML/Graphics.hpp>

class Button : public sf::RectangleShape
{
    public:
        Button(const int x, const int y, const int width, const int height, const std::string & text);   
    protected:
        sf::Color color_;
        sf::Text text_;
};
