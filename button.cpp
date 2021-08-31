#include "button.h"



Button::Button(const int x, const int y, const std::string& text, const sf::Font & font)
    : sf::Text(text,font)
{
    setPosition(x, y);
}
