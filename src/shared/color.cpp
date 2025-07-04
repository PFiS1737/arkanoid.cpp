module;

#include <allegro5/color.h>

module shared.color;

import configs;

Color::Color(unsigned char r, unsigned char g, unsigned char b, size_t score)
    : color{al_map_rgb(r, g, b)}, score(score) {
}

Color::Color(const string &colorName) : Color(fromString(colorName)) {
}

bool Color::operator==(const Color &other) const {
  return color.r == other.color.r && color.g == other.color.g && color.b == other.color.b && color.a == other.color.a &&
         score == other.score;
}

Color::operator ALLEGRO_COLOR() const {
  return color;
}

Color Color::fromString(const string &colorName) {
  static const unordered_map<string, Color> map = {
      {"red", COLOR_RED},         {"green", COLOR_GREEN},   {"blue", COLOR_BLUE},   {"yellow", COLOR_YELLOW},
      {"magenta", COLOR_MAGENTA}, {"cyan", COLOR_CYAN},     {"white", COLOR_WHITE}, {"black", COLOR_BLACK},
      {"gold", COLOR_GOLD},       {"silver", COLOR_SILVER},
  };

  auto it = map.find(colorName);
  if (it != map.end()) {
    return it->second;
  }

  cerr << "No color found for name: '" << colorName << "', using COLOR_WHITE." << endl;

  return COLOR_WHITE;
}
