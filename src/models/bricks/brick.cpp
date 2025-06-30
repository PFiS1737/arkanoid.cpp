#include "brick.hpp"
#include "../../display.hpp"

Brick::Brick(const Vec2 &center, const Color &color, const Bonus &bonus)
    : Bounceable{center, BRICK_WIDTH, BRICK_HEIGHT, color}, bonus{bonus} {
}

size_t Brick::getScore() const {
  return color.score;
}

void Brick::hit() {
  destroyed = true;
}

void Brick::draw() const {
  Rectangle::draw();

  string bonus = this->bonus;
  if (!bonus.empty()) {
    al_draw_text(Display::fontBrick, COLOR_BLACK, center.x - 3, SCREEN_HEIGHT - center.y - height / 2 - 3,
                 ALLEGRO_ALIGN_CENTER, bonus.c_str());
  }
}
