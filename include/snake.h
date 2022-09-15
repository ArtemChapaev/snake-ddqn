#pragma once

#include <string>
#include <list>

#include "settings.h"

#define SNAKE_LENGTH 5
#define SNAKE_SPEED 300000

const float STANDART_FOR_X = 0.4;
const float STANDART_FOR_Y = 0.6;

const float INDEX_FOR_X = 1. / 7;

enum Direction {
    up,
    right,
    down,
    left
};

class Position {
public:
    Position(unsigned x = 0, unsigned y = 0);

    bool operator==(Position other);
    unsigned get_x();
    unsigned get_y();

private:
    unsigned x;
    unsigned y;
};

class Snake {
public:
    Snake(Settings);
    Position get_head();
    Position get_tail();
    std::list<Position> get_snake();
    Position get_next();
    Direction get_direction();
    void set_direction(Direction dir);
    float get_speed_coef();
    Position move();
    int increase_length(Position);

private:
    std::list<Position> snake;
    unsigned length;
    Direction direction;
    float speed_coef;
};
