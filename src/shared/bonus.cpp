module shared.bonus;

import configs;

Bonus::Bonus(Type type) : type{type}, color{COLOR_BLACK} {
  if (type != Type::None) throw runtime_error("Only Type::None is allowed with this constructor");
}

Bonus::Bonus(Type type, const Color &color) : type{type}, color{color}, isStatic{true} {
}

Bonus::Bonus(Type type, const Color &color, double duration) : type{type}, color{color}, duration{duration} {
}

Bonus::Bonus(const string &bonusName) : Bonus{fromString(bonusName)} {
}

bool Bonus::operator==(const Bonus &other) const {
  return type == other.type;
}

Bonus::operator Type() const {
  return type;
}

Bonus Bonus::fromString(const string &bonusName) {
  static const unordered_map<string, Bonus> map = {
      {"", BONUS_NONE},
      {"extra_life", BONUS_EXTRA_LIFE},
      {"slow_ball", BONUS_SLOW_BALL},
      {"wide_racket", BONUS_WIDE_RACKET},
      {"sticky_racket", BONUS_STICKY_RACKEY},
      {"split_ball", BONUS_SPLIT_BALL},
      {"laser", BONUS_LASER},
  };

  auto it = map.find(bonusName);
  if (it != map.end()) {
    return it->second;
  }

  cerr << "No bonus found for name: '" << bonusName << "', using BONUS_NONE." << endl;

  return BONUS_NONE;
}

Bonus::operator string() const {
  switch (type) {
    case Type::None:
      return "";
    case Type::ExtraLife:
      return "";
    case Type::SlowBall:
      return "󱙷";
    case Type::WideRacket:
      return "󱀆";
    case Type::StickyRacket:
      return "󰤄";
    case Type::SplitBall:
      return "󰃻";
    case Type::Laser:
      return "󱐋";
    default:
      throw runtime_error("Unknown bonus type");
  }
}
