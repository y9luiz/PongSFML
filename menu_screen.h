#pragma once
#include "screen.h"
#include "button.h"
#include <SFML/Graphics.hpp>

class MenuScreen : public Screen 
{

    public:
        MenuScreen(const int width, const int height, const std::string tittle);
		void run() override;
        inline void setButton(const int x, const int y, const int width, const int height, sf::Texture & texture)
        {
            play_button_ = std::make_shared<Button>(x, y, width, height, texture);
        }
    protected:
        std::shared_ptr<Button> play_button_;
        bool is_running_ = false; 
        void handleInput() override;
        sf::Texture texture;

};
