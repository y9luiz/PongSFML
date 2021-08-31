#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
class Button : public sf::Text
{
    public:
        Button::Button(const int x, const int y, const std::string& text, const sf::Font & font);

        inline bool isInside(int x, int y)
        {
           
            sf::FloatRect global_rect = getGlobalBounds();
            return global_rect.contains(x, y);
                    
        }
    protected:
        std::shared_ptr<sf::Text> text_view_;
};
