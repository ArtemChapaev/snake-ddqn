#pragma once

#include <string>
#include <list>

#define SNAKE_LENGTH 5
#define SNAKE_SPEED 600000

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
    void set_x(unsigned);
    void set_y(unsigned);

private:
    unsigned x;
    unsigned y;
};

class Snake {
public:
    Snake(unsigned map_len, unsigned map_wid, float speed_coef = 1.);
    Position get_head();
    Position get_tail();
    Position get_next();
    Direction get_direction();
    void set_direction(Direction dir);
    unsigned get_speed_coef();
    Position move();
    int increase_length(Position);

    friend class MapModel; // метод, а не класс

private:
    std::list<Position> snake;
    unsigned length;
    Direction direction;
    float speed_coef;
};
