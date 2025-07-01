export module shared.vec2;

export struct Vec2 final {
  double x;
  double y;

  Vec2(double x = 0, double y = 0);

  double getModule() const;
  const Vec2 &normalize();
  Vec2 normalized() const;
  Vec2 rotated(double detla) const;
  Vec2 clamped(const Vec2 &min, const Vec2 &max) const;
  bool operator==(const Vec2 &other) const;
  Vec2 operator+(const Vec2 &vec) const;
  Vec2 &operator+=(const Vec2 &vec);
  Vec2 operator-(const Vec2 &vec) const;
  Vec2 &operator-=(const Vec2 &vec);
  Vec2 operator-() const;
  Vec2 operator*(double scalar) const;
  Vec2 &operator*=(double scalar);
};
