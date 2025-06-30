#include "controller.hpp"
#include "models/bricks/gold.hpp"
#include "models/bricks/silver.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

Controller::Controller() : board{make_shared<Board>()}, display{Display(board)} {
  board->init();

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
      }

      if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
        auto code = event.keyboard.keycode;

        if (code == ALLEGRO_KEY_Q || code == ALLEGRO_KEY_ESCAPE) {
          done = true;
        }

        if (code == ALLEGRO_KEY_SPACE) {
          if (!board->releaseBall()) board->shootLaser();
        }

        if (code == ALLEGRO_KEY_R) {
          al_stop_timer(timer);
          loadLevel();
        }
      }

      if (event.type == ALLEGRO_EVENT_TIMER) {
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
  board->setRacketX(mouseState.x);

  board->update(1.0 / UPS);

  if (tick >= UPS / FPS) {
    draw = true;
    tick = 0;
  } else {
    tick++;
  }
}

void Controller::checkWinOrLose() {
  if (board->isWin()) {
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
  ifstream file(LEVEL_PATH);
  if (!file.is_open()) {
    throw runtime_error("Failed to open file: " + LEVEL_PATH);
  }

  vector<shared_ptr<Brick>> bricks;

  string line;
  while (getline(file, line)) {
    if (line.empty() || line.starts_with("#")) continue;

    istringstream iss(line);
    double x, y;
    string color;
    if (!(iss >> x >> y >> color)) {
      cout << "Failed to read line: '" << line << "', skipping" << endl;
      continue;
    }

    string bonus;
    iss >> bonus;

    x += BORDER_THICKNESS;
    y += BORDER_THICKNESS;

    Vec2 pos = {x, y};

    if (color == COLOR_GOLD) {
      bricks.push_back(Brick::make<GoldBrick>(pos));
    } else if (color == COLOR_SILVER) {
      bricks.push_back(Brick::make<SilverBrick>(pos, bonus));
    } else {
      bricks.push_back(Brick::make<Brick>(pos, color, bonus));
    }
  }

  file.close();

  board->reset(bricks);

  al_start_timer(timer);
}

void Controller::setupAllegro() {
  if (!al_install_keyboard()) {
    throw runtime_error("Failed to install the keyboard");
  }

  if (!al_install_mouse()) {
    throw runtime_error("Failed to install the mouse");
  }

  timer = al_create_timer(1.0 / UPS);
  if (!timer) {
    throw runtime_error("Failed to create timer");
  }

  eventQueue = al_create_event_queue();
  if (!eventQueue) {
    throw runtime_error("Failed to create event queue");
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
