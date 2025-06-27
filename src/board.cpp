#include "board.hpp"

Board::Board() {
  racket =
      make_shared<Racket>(Vec2{BOARD_WIDTH / 2 + BORDER_THICKNESS, RACKET_Y_POSITION}, RACKET_WIDTH, RACKET_HEIGHT);

  // left
  borders.push_back(make_shared<Border>(Vec2{0, BOARD_HEIGHT}, Vec2{BORDER_THICKNESS, 0}));
  // right
  borders.push_back(make_shared<Border>(Vec2{SCREEN_WIDTH - BORDER_THICKNESS, BOARD_HEIGHT}, Vec2{SCREEN_WIDTH, 0}));
  // top
  borders.push_back(make_shared<Border>(Vec2{0, BOARD_HEIGHT},
                                        Vec2{BOARD_WIDTH + BORDER_THICKNESS, BOARD_HEIGHT - BORDER_THICKNESS}));
}

void Board::update(double dt) {
  if (dt == 0) return;

  ball->update(dt);
}

void Board::reset() {
  life = INITIAL_NUM_LIVES;
  score = 0;
  ball = Ball::newBall();
  bricks.clear();
}
