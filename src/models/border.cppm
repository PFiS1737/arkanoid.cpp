export module models.border;

import shared.bounceable;
import shared.vec2;

export struct Border final : Bounceable {
  Border(const Vec2 &topLeft, const Vec2 &bottomRight);

  Border(const Border &) = delete;
  Border(Border &&) = delete;
  Border &operator=(const Border &) = delete;
  Border &operator=(Border &&) = delete;
};
