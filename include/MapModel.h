#pragma once

#include "snake.h"

enum Cell {
    EMPTY,
    SNAKE,
    WALL,
    FRUIT
};

class MapModel {
public:
    MapModel(unsigned, unsigned);
    //~MapModel(); // неработающий деструктор
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
