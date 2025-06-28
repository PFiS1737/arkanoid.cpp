#pragma once

#include <allegro5/color.h>
#include <string>

using namespace std;

struct Color final {
  ALLEGRO_COLOR color;
  size_t score;

  static Color fromString(const string &colorName);

  Color(unsigned char r, unsigned char g, unsigned char b, size_t score = 0);

  bool operator==(const Color &other) const;
  operator ALLEGRO_COLOR() const;
};
