#pragma once

#include <cstdlib>
#include <vector>

#include "settings.h"
#include "snake.h"

const unsigned kStateSize = 32;

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
    std::pair<unsigned, unsigned> get_bonus_coords();

   private:
    bool validate_teleports(unsigned, unsigned);

    Cell **field;
    const unsigned length;
    const unsigned width;
};

MapModel read_map_from_file(Settings);
void write_map_to_file(MapModel &);

struct State {
    State(double bu = 0, double br = 0, double bd = 0, double bl = 0, double dbu = 0, double dbr = 0,
          double dbd = 0, double dbl = 0)
        : bonus_up(bu),
          bonus_right(br),
          bonus_down(bd),
          bonus_left(bl),
          dist_barrier_up(dbu),
          dist_barrier_right(dbr),
          dist_barrier_down(dbd),
          dist_barrier_left(dbl){};

    double bonus_up;
    double bonus_right;
    double bonus_down;
    double bonus_left;
    double dist_barrier_up;
    double dist_barrier_right;
    double dist_barrier_down;
    double dist_barrier_left;
};

State get_state(MapModel &, Snake);
std::vector<double> state_struct_to_vector(const State &);
