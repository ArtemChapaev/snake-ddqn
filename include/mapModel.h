#pragma once

#include <cstdlib>

#include "settings.h"
#include "snake.h"

enum Cell {
// Cell types
    empty,
    snake_head,
    snake,
    wall,
    teleport,
    bonus,
    antibonus,
    speed_bonus,
    speed_antibonus
};

class MapModel {
// Class for map data
public:
    MapModel(Settings settings);
    ~MapModel();

    void put_snake(Snake);
    void generate_bonus(Cell);
    void clear_cell(Position);
    Cell check_cell(unsigned, unsigned);
    unsigned get_width();
    unsigned get_length();
private:
    Cell **field;
    const unsigned length;
    const unsigned width;
};
