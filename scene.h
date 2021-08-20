#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "screen.h"
#include <cassert>
class Scene
{
    public:
            enum class Type{
                MENU,
                PLAY
            };
            Scene(Screen * parent_screen): screen_(parent_screen)
            {

            }
            void drawObjects(sf::Color backgroind_color = sf::Color::Black)
            {
                //assert(screen_ != nullptr);
                screen_->clear(backgroind_color);
                for(auto const & obj:objects_)
                {
                    screen_->draw(*obj);
                }
            }
            void addObject(std::shared_ptr<sf::Drawable> obj)
            {
                objects_.push_back(obj);
            }
            std::vector<std::shared_ptr<sf::Drawable>>   getObjects()
            {
                return objects_;
            }
            void clear()
            {
                objects_.clear();
            }
    private:
        Screen * screen_;
        std::vector<std::shared_ptr<sf::Drawable>> objects_;
};