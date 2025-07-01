module;

#include <allegro5/color.h>

export module shared.color;

import std;

using namespace std;

export struct Color final {
  ALLEGRO_COLOR color;
  size_t score;

  Color(unsigned char r, unsigned char g, unsigned char b, size_t score = 0);
  Color(const string &colorName);

  bool operator==(const Color &other) const;
  operator ALLEGRO_COLOR() const;

private:
  static Color fromString(const string &colorName);
};
