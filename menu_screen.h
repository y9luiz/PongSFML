#pragma once
#include "screen.h"
#include <SFML/Graphics.hpp>

class MenuScreen : public Screen 
{

    public:
        MenuScreen(const int width, const int height, const std::string tittle);
		void run() override;
    protected:
        
        void handleInput() override;

};
