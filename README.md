# Tic Tac Toe - Mini Game 🎮

A console-based Tic Tac Toe game built in **C++** that demonstrates core programming concepts such as loops, arrays, and conditional logic.

---

## 📌 Project Overview

This project is developed as part of the **Thiranex C++ Internship Program**. It is an interactive two-mode Tic Tac Toe game featuring dynamic board display, win/loss/draw detection, AI opponent, and a replay system.

---

## ✨ Features

- 👥 **Two Player Mode** — Play against a friend locally with custom player names
- 🤖 **Player vs AI Mode** — Challenge a smart AI that blocks and attacks
- 🏆 **Win / Loss / Draw Detection** — Automatically detects end-of-game conditions
- 📊 **Scoreboard** — Tracks wins, losses, and draws across multiple rounds
- 🔄 **Replay Option** — Play again without restarting the program
- 🔁 **Score Reset** — Reset the scoreboard anytime from the menu

---

## 🛠️ Tech Stack

- **Language:** C++
- **Concepts Used:** 2D Arrays, Loops, Conditional logic, Functions, Game state management

---

## 🚀 How to Run

### Prerequisites
- A C++ compiler (g++ recommended)

### Compile & Run

```bash
# Compile
g++ main.cpp -o tictactoe

# Run on Linux/Mac
./tictactoe

# Run on Windows
tictactoe.exe
```

---

## 📂 File Structure

```
Mini-game-tictactoe-cpp/
│
├── main.cpp          # Main source code
├── README.md         # Project documentation
└── .gitignore        # Ignores any generated files
```

---

## 📸 Menu Preview

```
  ╔══════════════════════════════════════════╗
  ║       TIC TAC TOE - MINI GAME           ║
  ╚══════════════════════════════════════════╝

  📊  Scoreboard → X: 2  O: 1  Draws: 0

       1.  Two Player Mode
       2.  Player vs AI
       3.  Reset Scores
       4.  Exit
```

### Board Display

```
  ┌───┬───┬───┐
  │ X │ 2 │ 3 │
  ├───┼───┼───┤
  │ 4 │ O │ 6 │
  ├───┼───┼───┤
  │ 7 │ 8 │ X │
  └───┴───┴───┘
```

---

## 🎯 How to Play

- The board has positions numbered **1 to 9** (left to right, top to bottom)
- Players take turns entering a position number to place their mark
- First to get **3 in a row** (horizontal, vertical, or diagonal) wins!
- If all 9 cells are filled with no winner, it's a **draw**

---

## 📝 Expected Outcome

An interactive game with dynamic board display, win/loss detection, and replay functionality, showcasing effective implementation of game logic.

---

## 👨‍💻 Author

Developed by **ARULSELVAN** as part of the Codsoft Internship Program.
