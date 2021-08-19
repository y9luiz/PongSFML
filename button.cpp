#include "button.h"

Button::Button(const int x, const int y, const int width, const int height, const sf::Texture& texture) :
    sf::Sprite(texture), width_(width),height_(height)//, sf::Rect<int>(x, y, width, height))
{   
    texture_ = std::make_shared<sf::Texture>(texture);
    setTextureRect(sf::Rect<int>(0, 0, width, height));
    setPosition(x, y);
}


Button::Button(const int x, const int y, const int width, const int height) : width_(width), height_(height)
{
    
    texture_ = std::make_shared<sf::Texture>();
    setTextureRect(sf::Rect<int>(x,y,width,height));
    setTexture(*texture_);
}

