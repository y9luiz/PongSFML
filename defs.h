#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Color.hpp>

const std::string ASSERTS_PATH = "Assets";

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

const std::string FONT_SCORE_PATH = "Assets/CollegiateOutlineFLF.ttf";
const sf::Color FONT_SCORE_COLOR = sf::Color(255, 255, 255);
const int FONT_SCORE_SIZE = 30;
const std::string FONT_PAUSE_PATH = "Assets/CollegiateOutlineFLF.ttf";
const sf::Color FONT_PAUSE_COLOR = sf::Color(255, 255, 255);
const int FONT_PAUSE_SIZE = 50;

// PLAYERS DEFINITIONS
const sf::Vector2f PADDLE_SIZE(20,150);
const sf::Vector2f PADDLE_SPEED(1, 10);

// PLAYER 1 DEFINITIONS 
const float PLAYER_1_X_POS = 0;
const float PLAYER_1_Y_POS = 240;
const sf::Rect<float> PLAYER_1_RECT(PLAYER_1_X_POS, PLAYER_1_Y_POS, PADDLE_SIZE.x, PADDLE_SIZE.y);
const sf::Color PLAYER_1_COLOR = sf::Color(255, 0, 0);

// PLAYER 2 DEFINITIONS 
const float PLAYER_2_X_POS = WINDOW_WIDTH - PADDLE_SIZE.x;
const float PLAYER_2_Y_POS = 120;
const sf::Rect<float> PLAYER_2_RECT(PLAYER_2_X_POS, PLAYER_2_Y_POS, PADDLE_SIZE.x, PADDLE_SIZE.y);
const sf::Color PLAYER_2_COLOR = sf::Color(0, 0, 255);

// BALL DEFINITIONS
const float BALL_RADIUS = 10;
const sf::Vector2f BALL_INIT_POSITION = sf::Vector2f((PLAYER_1_X_POS + PLAYER_2_X_POS) / 2, PLAYER_1_Y_POS);
const sf::Vector2f BALL_SPEED(15, 3);
const sf::Color BALL_COLOR(0, 255, 0);

//const sf::Vector2f BALL_INIT_POSITION = sf::Vector2f(PLAYER_1_X_POS, PLAYER_1_Y_POS);

//SPEED INCREASEMENT PER LEVEL
const int SPEED_INCX = 0.5;
const int SPEED_INCY = 0.02;
const int SPEED_INCP = 0.2;

// OBSTACLES DEFINITIONS
const sf::Color OBSTACLE_COLOR = sf::Color(69, 129, 142);
const sf::Vector2f OBSTACLE_SIZE(15, 140);
const sf::Rect<float> LEVEL1_OBST_RECT(
    WINDOW_WIDTH/2 - OBSTACLE_SIZE.x/2, WINDOW_HEIGHT/2 - OBSTACLE_SIZE.y/2,
    OBSTACLE_SIZE.x, OBSTACLE_SIZE.y
    );
const sf::Rect<float> LEVEL2_OBST1_RECT(
    200, WINDOW_HEIGHT/2 - OBSTACLE_SIZE.y/2,
    OBSTACLE_SIZE.x, OBSTACLE_SIZE.y - 30
    );
const sf::Rect<float> LEVEL2_OBST2_RECT(
    WINDOW_WIDTH - 200, WINDOW_HEIGHT/2 - OBSTACLE_SIZE.y/2,
    OBSTACLE_SIZE.x, OBSTACLE_SIZE.y - 30
    );
const sf::Rect<float> LEVEL3_OBST1_RECT(
    150, 50,
    OBSTACLE_SIZE.x, OBSTACLE_SIZE.y
    );
const sf::Rect<float> LEVEL3_OBST2_RECT(
    WINDOW_WIDTH - 150, WINDOW_HEIGHT - OBSTACLE_SIZE.y - 50,
    OBSTACLE_SIZE.x, OBSTACLE_SIZE.y
    );
