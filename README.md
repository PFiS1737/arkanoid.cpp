# arkanoid.cpp

A modern C++ implementation of the classic **Arkanoid** game.

## 🕹️ Play

> Gameplay instructions coming soon!

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

```bash
just       # build the project
just run   # build and run the game
```

> See [`justfile`](./justfile) and [`xmake.lua`](./xmake.lua) for more details.
