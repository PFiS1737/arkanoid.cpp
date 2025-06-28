#pragma once

#include "color.hpp"
#include "vec2.hpp"

// Paths
const std::string FONT_PATH = "ressources/font.ttf"; // JetBrainsMonoNLNerdFont-Regular
const std::string LEVEL_PATH = "ressources/level.txt";

// Screen
inline constexpr float SCREEN_WIDTH = 1090;
inline constexpr float SCREEN_HEIGHT = 1080;
inline constexpr double FPS = 125;

// Board
inline constexpr double BOARD_WIDTH = 1050;
inline constexpr double BOARD_HEIGHT = 980;
inline constexpr double UPS = 125;

// Ball
inline constexpr double BALL_RADIUS = 10;
inline constexpr double BALL_SPEED = 500;
const Vec2 BALL_INITIAL_DIRECTION{1, 1};

// Border
inline constexpr double BORDER_THICKNESS = 20;

// Brick
inline constexpr double BRICK_WIDTH = 70;
inline constexpr double BRICK_HEIGHT = 20;

// Racket
inline constexpr double RACKET_WIDTH = 100;
inline constexpr double RACKET_HEIGHT = 25;
inline constexpr double RACKET_Y_POSITION = 50;

// Initial number of lives
inline constexpr unsigned INITIAL_NUM_LIVES = 3;

// Colors
const Color COLOR_RED = {255, 0, 0, 1};
const Color COLOR_GREEN = {0, 255, 0, 2};
const Color COLOR_BLUE = {0, 0, 255, 3};
const Color COLOR_YELLOW = {255, 255, 0, 4};
const Color COLOR_MAGENTA = {255, 0, 255, 5};
const Color COLOR_CYAN = {0, 255, 255, 6};
const Color COLOR_WHITE = {255, 255, 255};
const Color COLOR_BLACK = {0, 0, 0};
