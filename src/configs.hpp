#pragma once

#include "vec2.hpp"
#include <allegro5/color.h>
#include <string>

// Paths
const std::string FONT_PATH = "ressources/font.ttf"; // JetBrainsMonoNLNerdFont-Regular
const std::string LEVEL_PATH = "ressources/level.txt";

// Screen
inline constexpr float SCREEN_WIDTH = 1020;
inline constexpr float SCREEN_HEIGHT = 1080;
inline constexpr double FPS = 125;

// Board
inline constexpr double BOARD_WIDTH = 980;
inline constexpr double BOARD_HEIGHT = 980;
inline constexpr double UPS = 125;

// Ball
inline constexpr double BALL_RADIUS = 10;
inline constexpr double BALL_SPEED = 500;
const Vec2 BALL_INITIAL_DIRECTION{0, 1};

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
const ALLEGRO_COLOR COLOR_BLACK = al_map_rgb(0, 0, 0);
const ALLEGRO_COLOR COLOR_WHITE = al_map_rgb(255, 255, 255);
const ALLEGRO_COLOR COLOR_RED = al_map_rgb(255, 0, 0);
