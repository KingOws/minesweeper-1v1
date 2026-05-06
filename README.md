# 💣 Minesweeper 1v1

> A competitive two-player Minesweeper game with three difficulty modes, built in C++ with SFML.

![Menu Screenshot](screenshots/menu.png)

---

## About

A twist on classic Minesweeper. Two players race to clear their board, first to finish wins. Built as a collaborative project with a focus on clean game logic and smooth rendering via SFML.

> **Co-developed with [@SNCSamitek](https://github.com/SNCSamitek)**

---

## Features

- 🆚 1v1 competitive gameplay
- 🎚️ Three difficulty modes — Easy, Medium, Hard
- 🖱️ Full Minesweeper Game (Singleplayer Included)
- 🏆 Win detection and game-over states
- 🎨 SFML-powered rendering with clean UI
- 🎬 Scene Managed Architecture

---

## Screenshots

| Easy | Medium | Hard |
|-----------|-----------|-----------|
| ![easy](screenshots/easy.png) | ![medium](screenshots/medium.png) | ![hard](screenshots/hard.png) |

---

## Tech Stack

- **Language:** C++
- **Graphics:** SFML
- **Build System:** CMake

---

## Getting Started

### Prerequisites

- CMake ≥ 3.16
- SFML installed on your system
- A C++ Compiler

### Build

```bash
git clone https://github.com/KingOws/minesweeper-1v1
cd minesweeper-1v1
mkdir build && cd build
```
WINDOWS
```bash
cmake ..
cmake --build .
./minesweeper.exe
```

MACOS
```bash
mkdir build && cd build
cmake ..
make
./minesweeper
```

---

## Left to Complete

- Networking

---

## Authors

- [@KingOws](https://github.com/KingOws)
- [@SNCSamitek](https://github.com/SNCSamitek)
