#include "silver.hpp"
#include "../../display.hpp"
#include <allegro5/allegro_primitives.h>

SilverBrick::SilverBrick(const Vec2 &center, const Bonus &bonus) : Brick{center, COLOR_SILVER, bonus} {
}

void SilverBrick::hit() {
  if (--durability == 0) destroyed = true;
}

void SilverBrick::draw() const {
  Brick::draw();

  // TODO: better way to display durability
  al_draw_text(Display::fontBrick, COLOR_BLACK, center.x - width / 2 + 10, SCREEN_HEIGHT - center.y - height / 2 - 3,
               ALLEGRO_ALIGN_CENTER, to_string(durability).c_str());
}
