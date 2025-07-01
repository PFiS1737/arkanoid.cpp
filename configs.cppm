export module configs;

import shared.bonus;
import shared.color;
import shared.vec2;
import std;

using namespace std;

// Initial number of lives
export inline constexpr unsigned INITIAL_NUM_LIVES = 3;

// Paths
export const string FONT_PATH = "ressources/font.ttf"; // JetBrainsMonoNLNerdFont-Regular
export const string LEVEL_PATH = "ressources/level.txt";

// Colors
export const Color COLOR_RED = {255, 0, 0, 1};
export const Color COLOR_GREEN = {0, 255, 0, 2};
export const Color COLOR_BLUE = {0, 0, 255, 3};
export const Color COLOR_YELLOW = {255, 255, 0, 4};
export const Color COLOR_MAGENTA = {255, 0, 255, 5};
export const Color COLOR_CYAN = {0, 255, 255, 6};
export const Color COLOR_WHITE = {255, 255, 255};
export const Color COLOR_BLACK = {0, 0, 0};
export const Color COLOR_SILVER = {184, 217, 243, 10};
export const Color COLOR_GOLD = {255, 200, 0};

// Screen
export inline constexpr float SCREEN_WIDTH = 1090;
export inline constexpr float SCREEN_HEIGHT = 1080;
export inline constexpr double FPS = 125;

// Board
export inline constexpr double BOARD_WIDTH = 1050;
export inline constexpr double BOARD_HEIGHT = 980;
export inline constexpr double UPS = 125;

// Ball
export inline constexpr double BALL_RADIUS = 10;
export inline constexpr double BALL_SPEED = 500;
export const Color BALL_COLOR = COLOR_WHITE;
export const Vec2 BALL_INITIAL_DIRECTION{0, 1};

// Border
export inline constexpr double BORDER_THICKNESS = 20;
export const Color BORDER_COLOR = COLOR_WHITE;

// Brick
export inline constexpr double BRICK_WIDTH = 70;
export inline constexpr double BRICK_HEIGHT = 20;
export inline constexpr size_t BRICK_SILVER_DURABILITY = 2;

// Racket
export inline constexpr double RACKET_WIDTH = 100;
export inline constexpr double RACKET_HEIGHT = 25;
export inline constexpr double RACKET_Y_POSITION = 50;
export const Color RACKET_COLOR = COLOR_WHITE;

// Pill
export inline constexpr double PILL_RADIUS = 6;
export inline constexpr double PILL_SPEED = 100;

// Laser
export inline constexpr double LASER_LENGTH = 40;
export inline constexpr double LASER_SPEED = 1000;

// Bonus
export const Bonus BONUS_NONE = {Bonus::Type::None};
export const Bonus BONUS_EXTRA_LIFE = {Bonus::Type::ExtraLife, COLOR_GREEN};
export const Bonus BONUS_SLOW_BALL = {Bonus::Type::SlowBall, COLOR_YELLOW, 10};
export const Bonus BONUS_WIDE_RACKET = {Bonus::Type::WideRacket, COLOR_BLUE, 10};
export const Bonus BONUS_STICKY_RACKEY = {Bonus::Type::StickyRacket, COLOR_MAGENTA};
export const Bonus BONUS_SPLIT_BALL = {Bonus::Type::SplitBall, COLOR_CYAN};
export const Bonus BONUS_LASER = {Bonus::Type::Laser, COLOR_RED, 5};

export constexpr double BONUS_SLOW_BALL_RATE = 0.666;
export constexpr double BONUS_WIDE_RACKET_RATE = 1.5;
