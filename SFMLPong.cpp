﻿// SFMLPong.cpp : Defines the entry point for the application.
//

#include <chrono>
#include <thread>

#include "SFMLPong.h"
#include "game_screen.h"

using namespace std;
using namespace chrono_literals;

int main()
{
	GameScreen game_screen(WINDOW_WIDTH,WINDOW_HEIGHT,"Play");
	
	game_screen.run();
	
	return 0;
}
