#pragma once

#include <iostream>
#include <list>
#include <string>

#include "settings.h"

const unsigned SNAKE_LENGTH = 5;

const double STANDART_FOR_X = 0.4;
const double STANDART_FOR_Y = 0.6;

const double INDEX_FOR_X = 1. / 7;

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
    /// Класс позиции с координатами x, y.
    /// Используется для хранения тела змеи.

    Position(unsigned x = 0, unsigned y = 0);

    bool operator==(Position other);
    unsigned get_x();
    unsigned get_y();

private:
    unsigned x;
    unsigned y;
};

class Snake {
    /// Класс-модель, реализующий одну из главных сущностей - змею.
    /// Хранит в себе методы взаимодействия игры со змеей.
    /// Хранит атрибут, влияющий на скорость игры.
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
