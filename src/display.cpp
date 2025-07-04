#include "display.hpp"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <stdexcept>

ALLEGRO_FONT *Display::font24 = nullptr;
ALLEGRO_FONT *Display::font50 = nullptr;
ALLEGRO_FONT *Display::fontBrick = nullptr;

Display::Display(const unique_ptr<Board> &board) : board(*board) {
  if (!al_init()) {
    throw runtime_error("Failed to initialize Allegro");
  }

  if (!al_init_primitives_addon()) {
    throw runtime_error("Failed to initialize Allegro primitives addon");
  };

  if (!al_init_font_addon() || !al_init_ttf_addon()) {
    throw runtime_error("Failed to initialize Allegro font/ttf addon");
  };

  display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
  if (!display) {
    throw runtime_error("Failed to create display");
  }

  ALLEGRO_MONITOR_INFO info;
  al_get_monitor_info(0, &info);

  int width = info.x2 - info.x1;
  int height = info.y2 - info.y1;

  int x = (width - SCREEN_WIDTH) / 2;
  int y = (height - SCREEN_HEIGHT) / 2;

  al_set_window_position(display, x, y);

  font24 = al_load_ttf_font(FONT_PATH.c_str(), 24, 0);
  if (!font24) {
    throw runtime_error("Failed to load font24");
  }

  font50 = al_load_ttf_font(FONT_PATH.c_str(), 50, 0);
  if (!font50) {
    throw runtime_error("Failed to load font50");
  }

  fontBrick = al_load_ttf_font(FONT_PATH.c_str(), BRICK_HEIGHT - 2, 0);
  if (!fontBrick) {
    throw runtime_error("Failed to load fontBrick");
  }
}

Display::~Display() {
  al_destroy_display(display);
  al_destroy_font(font24);
  al_destroy_font(font50);
  al_destroy_font(fontBrick);
  al_shutdown_font_addon();
  al_shutdown_ttf_addon();
  al_shutdown_primitives_addon();
}

void Display::draw() {
  const char gameTitle[] = "arkanoid.cpp";

  al_clear_to_color(COLOR_BLACK);

  al_draw_text(font24, COLOR_WHITE, SCREEN_WIDTH / 2 - 24, 30, ALLEGRO_ALIGN_CENTER, gameTitle);

  al_draw_text(font24, COLOR_WHITE, (SCREEN_WIDTH / 6), 50, ALLEGRO_ALIGN_CENTER, "Life : ");
  al_draw_text(font24, COLOR_WHITE, (SCREEN_WIDTH / 6) + 60, 50, ALLEGRO_ALIGN_CENTER, to_string(board.life).c_str());

  al_draw_text(font24, COLOR_WHITE, (5 * SCREEN_WIDTH / 6) - 30, 45, ALLEGRO_ALIGN_CENTER, "Score : ");
  al_draw_text(font24, COLOR_WHITE, (5 * SCREEN_WIDTH / 6) + 40, 45, ALLEGRO_ALIGN_CENTER,
               to_string(board.score).c_str());

  board.draw();

  al_flip_display();
}

string Display::getScore() {
  return "Your score is " + to_string(board.score);
}

void Display::displayLines3(string line1, string line2, string line3) {
  al_clear_to_color(COLOR_BLACK);

  al_draw_text(font50, COLOR_WHITE, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 50, ALLEGRO_ALIGN_CENTER, line1.c_str());
  al_draw_text(font50, COLOR_WHITE, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, ALLEGRO_ALIGN_CENTER, line2.c_str());
  al_draw_text(font50, COLOR_WHITE, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 50, ALLEGRO_ALIGN_CENTER, line3.c_str());

  al_flip_display();
}

void Display::gameOver() {
  displayLines3("GAME OVER !", getScore(), "Press any key to restart");
}

void Display::gameWin() {
  displayLines3("YOU WIN !", getScore(), "Press any key to restart");
}

void Display::gameLaunch() {
  displayLines3("Welcome in arkanoid.cpp Game!", "", "Press any key to start");
}

Display::operator ALLEGRO_DISPLAY *() {
  return display;
}
