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

   private:
    bool validate_teleports(unsigned, unsigned);

    Cell **field;
    const unsigned length;
    const unsigned width;
};

MapModel read_map_from_file(Settings);
void write_map_to_file(MapModel &);

struct State {
    State(double bu = 0, double bur = 0, double br = 0, double bdr = 0, double bd = 0, double bdl = 0,
          double bl = 0, double bul = 0, double dwu = 0, double dwur = 0, double dwr = 0, double dwdr = 0,
          double dwd = 0, double dwdl = 0, double dwl = 0, double dwul = 0, double dtu = 0, double dtl = 0,
          double dtur = 0, double dtr = 0, double dtdr = 0, double ddl = 0, double dtdl = 0, double dtul = 0,
          double hdu = 0, double hdr = 0, double hdd = 0, double hdl = 0)
        : bonus_up(bu),
          bonus_up_right(bur),
          bonus_right(br),
          bonus_down_right(bdr),
          bonus_down(bd),
          bonus_down_left(bdl),
          bonus_left(bl),
          bonus_up_left(bul),
          dist_wall_up(dwu),
          dist_wall_up_right(dwur),
          dist_wall_right(dwr),
          dist_wall_down_right(dwdr),
          dist_wall_down(dwd),
          dist_wall_down_left(dwdl),
          dist_wall_left(dwl),
          dist_wall_up_left(dwul),
          dist_snake_up(dtu),
          dist_snake_left(dtl),
          dist_snake_up_right(dtur),
          dist_snake_right(dtr),
          dist_snake_down_right(dtdr),
          dist_snake_down(ddl),
          dist_snake_down_left(dtdl),
          dist_snake_up_left(dtul),
          head_direction_up(hdu),
          head_direction_right(hdr),
          head_direction_down(hdd),
          head_direction_left(hdl) {};

    double bonus_up;
    double bonus_up_right;
    double bonus_right;
    double bonus_down_right;
    double bonus_down;
    double bonus_down_left;
    double bonus_left;
    double bonus_up_left;
    double dist_wall_up;
    double dist_wall_up_right;
    double dist_wall_right;
    double dist_wall_down_right;
    double dist_wall_down;
    double dist_wall_down_left;
    double dist_wall_left;
    double dist_wall_up_left;
    double dist_snake_up;
    double dist_snake_up_right;
    double dist_snake_right;
    double dist_snake_down_right;
    double dist_snake_down;
    double dist_snake_down_left;
    double dist_snake_left;
    double dist_snake_up_left;
    double head_direction_up;
    double head_direction_right;
    double head_direction_down;
    double head_direction_left;
};

State get_state(MapModel &, Snake);
std::vector<double> state_struct_to_vector(const State &);
