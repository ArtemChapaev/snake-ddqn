---
layout: default
title: Snake
permalink: /
---

## Introduction
Snake game was developed as an educational project for OOP practice at Bauman Moscow State Technical University.

Snake moves in a limited field and her goal is to eat as many fruits as possible without crashing into walls or herself. Snake increases its length when eating an apple and dies when it collides with itself or with a wall. Game is designed for one player. User controls direction of snake's head in 4 directions: up, down, left, right, and snake's tail follows.
User cannot stop the movement of snake. Program interface is implemented in UNIX console.

In development process, following were used: MVC pattern, OOP principles (encapsulation, inheritance, dynamic polymorphism).

## Showcase
<img src='https://github.com/ArtemChapaev/Snake/blob/Linux_version/docs/gameplay.gif?raw=true'/>

## Installation

````
git clone --recurse-submodules https://github.com/ArtemChapaev/Snake
cd Snake
bash setup.sh
build/snake
````

## Configuration
You can specify path to settings file by command-line flag -f (by default using "settings.txt" in game directory).

Example:
```
./snake -f "../example/path/settings.txt"
```

## Features
Right in game you can configure:
- map (size, solid walls, bonus apples, score display)
- type of graphics (symbolic or escape, color of bonuses)
- snake (speed, length change on a new level)
- control buttons
- create your own map (map constructor)

You can read more about settings on this [page](settings)

Also implemented:
- menu
- pause during game
- leaderboard
- deathscreen with game results

## Requirements
- Unix
- Git
- C++17 or higher
- Cmake >= 3.6

## License
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

