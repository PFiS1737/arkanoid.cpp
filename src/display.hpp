#pragma once

#include "board.hpp"
#include <allegro5/allegro_font.h>
#include <memory>

using namespace std;

class Display final {
  const Board &board;

  ALLEGRO_DISPLAY *display;

  string getScore();
  void displayLines3(string line1, string line2, string line3);

public:
  static ALLEGRO_FONT *font24;
  static ALLEGRO_FONT *font50;
  static ALLEGRO_FONT *fontBrick;

  Display(const unique_ptr<Board> &board);
  ~Display();

  Display(const Display &) = delete;
  Display(Display &&) = delete;
  Display &operator=(const Display &) = delete;
  Display &operator=(Display &&) = delete;

  void draw();

  void gameLaunch();
  void gameWin();
  void gameOver();

  operator ALLEGRO_DISPLAY *();
};
