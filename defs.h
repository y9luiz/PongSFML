#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const sf::Vector2f PADDLE_SIZE(30,150);

// PLAYERS DEFINITIONS
const sf::Vector2f PADDLE_SPEED(1, 5);;

// PLAYER 1 DEFINITIONS 
const float PLAYER_1_X_POS = 100;
const float PLAYER_1_Y_POS = 240;
const sf::Rect<float> PLAYER_1_RECT(PLAYER_1_X_POS, PLAYER_1_Y_POS, PADDLE_SIZE.x, PADDLE_SIZE.y);

// PLAYER 2 DEFINITIONS 
const float PLAYER_2_X_POS = 500;
const float PLAYER_2_Y_POS = 240;
const sf::Rect<float> PLAYER_2_RECT(PLAYER_2_X_POS, PLAYER_2_Y_POS, PADDLE_SIZE.x, PADDLE_SIZE.y);

// BALL DEFINITIONS
const float BALL_RADIUS = 10;
const sf::Vector2f BALL_INIT_POSITION = sf::Vector2f((PLAYER_1_X_POS + PLAYER_2_X_POS) / 2, PLAYER_1_Y_POS);
//const sf::Vector2f BALL_INIT_POSITION = sf::Vector2f(PLAYER_1_X_POS, PLAYER_1_Y_POS);