export module models.border;

import shared.bounceable;
import shared.vec2;
import std;

using namespace std;

export struct Border final : Bounceable {
  Border(const Vec2 &topLeft, const Vec2 &bottomRight);

  Border(const Border &) = delete;
  Border(Border &&) = delete;
  Border &operator=(const Border &) = delete;
  Border &operator=(Border &&) = delete;

  static unique_ptr<Border> make(const Vec2 &topLeft, const Vec2 &bottomRight);
};
