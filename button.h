#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
class Button : public sf::Sprite
{
    public:
        Button(const int x, const int y, const int width, const int height, const sf::Texture& texture);
        Button(const int x, const int y, const int width, const int height);
        inline bool isInside(int x, int y)
        {
            auto position = getPosition();
          
            return ((x >= position.x) && (x  <= position.x + width_) &&
                (y >= position.y) && (y  <= position.y + height_));
                    
        }
    protected:
        std::shared_ptr<sf::Texture>  texture_;
        int width_;
        int height_;


};
