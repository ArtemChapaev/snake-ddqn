#pragma once

#include "snake.h"

enum Cell {
    EMPTY,
    SNAKE_HEAD,
    SNAKE,
    WALL,
    TELEPORT,
    FRUIT
};

class MapModel {
public:
    MapModel(Settings settings);
    ~MapModel();
    void put_snake(Snake);
    void generate_fruit();
    void clear_cell(unsigned, unsigned);
    Cell check_cell(unsigned, unsigned);
    unsigned get_width();
    unsigned get_length();
private:
    Cell **field;
    unsigned length;
    unsigned width;
};
