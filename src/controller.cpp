#include "controller.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

Controller::Controller() : board{make_shared<Board>()}, display(Display(board)) {
  setupAllegro();
  startingGame();
}

Controller::~Controller() {
  if (timer) {
    al_destroy_timer(timer);
  }
  if (eventQueue) {
    al_destroy_event_queue(eventQueue);
  }
}

void Controller::process() {
  while (!done) {
    al_wait_for_event(eventQueue, nullptr);

    while (al_get_next_event(eventQueue, &event)) {
      if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        done = true;
      } else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
        if (event.keyboard.keycode == ALLEGRO_KEY_Q || event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
          done = true;
        }
      } else if (event.type == ALLEGRO_EVENT_TIMER) {
        handleTick();
      }
    }

    if (draw) {
      display.draw();
      draw = false;
    }
  }
}

void Controller::handleTick() {
  checkWinOrLose();

  al_get_mouse_state(&mouseState);
  board->racket->setCenterX(mouseState.x);

  board->update(1.0 / UPS);

  if (tick >= UPS / FPS) {
    draw = true;
    tick = 0;
  } else {
    tick++;
  }
}

void Controller::checkWinOrLose() {
  if (board->bricks.size() == 0) {
    al_stop_timer(timer);
    display.gameWin();
    waitStart();
    loadLevel();
  } else if (board->life == 0) {
    al_stop_timer(timer);
    display.gameOver();
    waitStart();
    loadLevel();
  }
}

void Controller::waitStart() {
  do {
    if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
      done = true;
      break;
    } else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
      if (event.keyboard.keycode == ALLEGRO_KEY_Q || event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
        done = true;
      }
      break;
    }

    al_get_next_event(eventQueue, &event);

    al_rest(0.001); // NOTE: prevent 100% CPU usage
  } while (true);
}

void Controller::loadLevel() {
  board->reset();

  ifstream file(LEVEL_PATH);
  if (!file.is_open()) {
    cerr << "Failed to open file: " << LEVEL_PATH << endl;
    exit(1);
  }

  vector<shared_ptr<Brick>> bricks;

  string line;
  while (getline(file, line)) {
    istringstream iss(line);
    double x, y;
    string color;
    if (!(iss >> x >> y >> color)) {
      // cout << "Failed to read line: '" << line << "', skipping" << endl;
      continue;
    }

    x += BORDER_THICKNESS;
    y += BORDER_THICKNESS;
    bricks.push_back(Brick::makeBrick(Vec2{x, y}, BRICK_WIDTH, BRICK_HEIGHT, Color::fromString(color)));
  }

  file.close();

  board->bricks = bricks;

  al_start_timer(timer);
}

void Controller::setupAllegro() {
  if (!al_install_keyboard()) {
    cerr << "Failed to install the keyboard" << endl;
    exit(1);
  }

  if (!al_install_mouse()) {
    cerr << "Failed to install the mouse" << endl;
    exit(1);
  }

  timer = al_create_timer(1.0 / UPS);
  if (!timer) {
    cerr << "Failed to create timer" << endl;
    exit(1);
  }

  eventQueue = al_create_event_queue();
  if (!eventQueue) {
    cerr << "Failed to create queue" << endl;
    exit(1);
  }

  al_register_event_source(eventQueue, al_get_display_event_source(display));
  al_register_event_source(eventQueue, al_get_keyboard_event_source());
  al_register_event_source(eventQueue, al_get_mouse_event_source());
  al_register_event_source(eventQueue, al_get_timer_event_source(timer));
}

void Controller::startingGame() {
  display.gameLaunch();
  waitStart();
  loadLevel();
}
