#pragma once

#include "board.hpp"
#include <allegro5/allegro_font.h>
#include <memory>

using namespace std;

class Display final {
  const shared_ptr<Board> board;

  ALLEGRO_DISPLAY *display;

  ALLEGRO_FONT *font24;
  ALLEGRO_FONT *font50;

  string getScore();
  void displayLines3(string line1, string line2, string line3);

public:
  Display(const shared_ptr<Board> &board);
  ~Display();

  void draw();

  void gameLaunch();
  void gameWin();
  void gameOver();

  operator ALLEGRO_DISPLAY *();
};
