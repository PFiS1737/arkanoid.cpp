# arkanoid.cpp

A modern C++ implementation of the classic **Arkanoid** game.

## 🕹️ Play

### ⌨️ Controls

The racket will follow the mouse movement. And, there are the following key bindings:

- `q`, `<esc>` - Quit the game
- `r` - Restart the current level
- `<space>` - Release the ball or shoot the laser (coming soon)

### ⚙️ Configuration

- Check [configs.hpp](./configs.hpp) for the game configuration options.
- Check [level.txt](./ressources/level.txt) for building your own levels.
  - Note that the bricks coordinates are relative to the bottom-left corner of the screen.
  - And make sure they are adjusted to the `size`'s defined in [configs.hpp](./configs.hpp).

## 🎯 Roadmap

- [x] Basic gameplay
- [x] More bricks types
  - [x] Silver Bricks: breakable only with multiple hits
  - [x] Gold Bricks: unbreakable
- [ ] Bonus pills
  - [x] Slow Ball
  - [x] Extra Life
  - [x] Wide Racket
  - [ ] Sticky Racket
  - [ ] Split Ball
  - [ ] Lazer

## 🐛 Known Issues

- [ ] Only the ball can actively bounce, which may cause the ball to enter the racket and bounce between its top and bottom surfaces from inside.

## 🛠️ Development

This project is easy to build and run with modern tool [`just`](https://github.com/casey/just).

### 🔧 Dependencies

#### CLI Tools

* `gcc` (with C++20 support)
* [`xmake`](https://xmake.io)
* [`just`](https://github.com/casey/just)

#### System Libraries

* [`allegro`](https://github.com/liballeg/allegro5) (version 5.0 or higher)

#### Development Tools (optional but recommended)

* `clangd` (for language server support)
* `clang-format` (for code formatting)
* `clang-tidy` (for static analysis)

### 🚀 Build & Run

> See [`justfile`](./justfile) and [`xmake.lua`](./xmake.lua) for more details.

```bash
just       # build the project
just run   # build and run the game
```


## References

- [Allegro 5 Documentation](https://liballeg.org/a5docs/5.2.10/index.html)
- [Raquette Baballe](https://github.com/LuxySs-Evr5/RaquetteBaballe) (another Arkanoid remake)
