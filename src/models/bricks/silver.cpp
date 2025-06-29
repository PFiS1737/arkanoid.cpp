#include "silver.hpp"
#include "../../display.hpp"
#include <allegro5/allegro_primitives.h>

SilverBrick::SilverBrick(const Vec2 &center) : Brick{center, COLOR_SILVER} {
}

bool SilverBrick::hit() {
  if (--durability == 0) return true;
  return false;
}

void SilverBrick::draw() const {
  Brick::draw();
  al_draw_text(Display::fontBrick, COLOR_BLACK, center.x, SCREEN_HEIGHT - center.y - height / 2 - 2,
               ALLEGRO_ALIGN_CENTER, to_string(durability).c_str());
}
