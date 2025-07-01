module;

#include <allegro5/allegro.h>

export module controller;

import display;
import board;
import std;

using namespace std;

export class Controller final {
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
  void waitStart();
  void loadLevel();

  void setupAllegro();
  void startingGame();

public:
  Controller();
  ~Controller();

  Controller(const Controller &) = delete;
  Controller(Controller &&) = delete;
  Controller &operator=(const Controller &) = delete;
  Controller &operator=(Controller &&) = delete;

  void process();
};
