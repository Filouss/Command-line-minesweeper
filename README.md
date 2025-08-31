# Command-line Minesweeper

A C++ command-line implementation of the classic Minesweeper game which i implemented for my C++ college course.

## Overview

This project allows you to play Minesweeper directly in your terminal. You can select from predefined difficulty levels or set custom board sizes and mine counts.

## How to Run

Run the semestralka.exe file in the build folder in your terminal

You can run the program in two ways:

### 1. Using Presets

- Beginner: `./semestralka beg` (9x9 board, 9 mines)
- Intermediate: `./semestralka int` (16x16 board, 40 mines)
- Expert: `./semestralka exp` (16x30 board, 99 mines)
- Help: `./semestralka --help`

### 2. Custom Mode

```bash
./semestralka [height] [width] [mine_count]
```
Example:
```bash
./semestralka 10 15 20
```

## Controls

- During the game, enter coordinates (e.g., `3 5`) to reveal a cell.
- To flag a cell as a potential mine, prefix with `f` (e.g., `f 3 5`).
- The board uses 0-based coordinates, with (0,0) at the lower left.

## Features

- Play with different board sizes and difficulties
- Flag cells that might contain mines
- Game ends with a win if all non-mine cells are uncovered, or a loss if a mine is triggered
- Help and error messages guide the user

> _Developed by [Filouss](https://github.com/Filouss)_

