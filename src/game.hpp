#pragma once

#include "display.hpp"

using namespace std;

class Game {
  bool done = false;
  bool draw = false;

  uint8_t tick = 0;

  shared_ptr<Board> board;
  Display display;

  ALLEGRO_TIMER *timer;
  ALLEGRO_EVENT_QUEUE *eventQueue;
  ALLEGRO_EVENT event;
  ALLEGRO_MOUSE_STATE mouseState;

  void handleTick();
  void checkWinOrLose();
  void waitKeyToRestart();
  void loadLevel();

  void setupAllegro();
  void startingGame();

public:
  Game();
  ~Game();

  void process();
};
