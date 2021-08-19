#include "button.h"

Button::Button(const int x, const int y, const int width, const int height, const sf::Texture& texture) :
    sf::Sprite(texture, sf::Rect<int>(x, y, width, height))
{   
    texture_ = std::make_shared<sf::Texture>(texture);
}


Button::Button(const int x, const int y, const int width, const int height)
{
    
    texture_ = std::make_shared<sf::Texture>();
    setTextureRect(sf::Rect<int>(x,y,width,height));
    setTexture(*texture_);
}

