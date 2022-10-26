#pragma once

#include <iostream>
#include <list>
#include <string>

#include "settings.h"

const unsigned kSnakeLength = 5;

const double kStandartForX = 0.4;
const double kStandartForY = 0.6;

const double kIndexForX = 1. / 7;

enum Keys {
    up,
    right,
    down,
    left,
    interruption,
    enter
};

class Position {
public:
    /// The class of the position with x, y coordinates.
    /// It is used to store the snake's body.

    Position(unsigned x = 0, unsigned y = 0);

    bool operator==(Position other);
    unsigned get_x();
    unsigned get_y();

private:
    unsigned x;
    unsigned y;
};

class Snake {
    /// Class that implements one of the main entities - a snake
    /// It stores the methods of interaction of the game with the snake.
    /// Stores attributes that affect the direction of movement, the speed of the game.
public:
    Snake(Settings, unsigned);

    Position get_head();
    Position get_tail();
    std::list<Position> get_snake();
    Position get_next();
    Keys get_direction();
    void set_direction(Keys dir);
    float get_speed_coef();
    Position move();
    int increase_length(Position);
    Position decrease_length();
    Position relocate_snake(Settings);

private:
    std::list<Position> snake;
    unsigned length;
    Keys direction;
    const float speed_coef;

    Position move_in_cell(Position);
};
