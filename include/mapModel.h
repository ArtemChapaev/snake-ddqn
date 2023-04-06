#pragma once

#include <cstdlib>
#include <vector>

#include "settings.h"
#include "snake.h"

enum Cell {
    empty_c,
    snake_head_c,
    snake_c,
    wall_c,
    teleport_c,
    bonus_c,
    antibonus_c,
    speed_bonus_c,
    speed_antibonus_c
};

class MapModel {
    // Class for map data
   public:
    MapModel(Settings);
    ~MapModel();

    void put_snake(Snake);
    void generate_bonus(Cell);
    void clear_cell(Position);
    Cell check_cell(unsigned, unsigned);
    void set_cell(unsigned, unsigned, Cell);
    unsigned get_width();
    unsigned get_length();

   private:
    bool validate_teleports(unsigned, unsigned);

    Cell **field;
    const unsigned length;
    const unsigned width;
};

std::vector<double> get_state(MapModel &, Snake);
MapModel read_map_from_file(Settings);
void write_map_to_file(MapModel &);
