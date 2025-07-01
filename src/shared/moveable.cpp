module shared.moveable;

Moveable::Moveable(const Vec2 &center, const Vec2 &dirVec, double speed)
    : center{center}, dirVec{dirVec.normalized()}, speed{speed} {
}

void Moveable::update(double dt) {
  center += (dirVec * speed * dt);
}
