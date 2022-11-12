#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

//#include "mapModel.h"
#include "cpp-terminal/base.hpp"

struct Settings {
    Settings(unsigned mL = 20, unsigned mW = 20, float sp = 1, bool sW = 0, bool sc = 1, bool bA = 1, unsigned vM = 1,
             bool rL = 0, char kU = 72, char kD = 80, char kR = 77, char kL = 75, char kP = 27, char kEn = 10,
             char kT = 116, char kW = 119, char kEm = 101,

             Term::RGB sC = Term::RGB{28, 180, 1}, Term::RGB eC = Term::RGB{0, 0, 0},
             Term::RGB wC = Term::RGB{100, 100, 100}, Term::RGB tC = Term::RGB{160, 160, 160},
             Term::RGB bC = Term::RGB{150, 0, 0}, Term::RGB aC = Term::RGB{255, 255, 1},
             Term::RGB sbC = Term::RGB{0, 0, 255}, Term::RGB saC = Term::RGB{255, 130, 2}) :

            map_length(mL), map_width(mW), speed(sp), solid_wall(sW), score(sc), bonus_apples(bA), view_mode(vM),
            reset_length(rL), key_up(kU), key_down(kD), key_right(kR), key_left(kL), key_pause(kP), key_enter(kEn),
            key_teleport(kT), key_wall(kW), key_empty(kEm),

            snake_color(sC), empty_color(eC), wall_color(wC), teleport_color(tC), bonus_color(bC), antibonus_color(aC),
            speed_bonus_color(sbC), speed_antibonus_color(saC) {};

    unsigned map_length;
    unsigned map_width;
    float speed;
    bool solid_wall;
    bool score;
    bool bonus_apples;
    unsigned view_mode;
    bool reset_length;
    char key_up;
    char key_down;
    char key_right;
    char key_left;
    char key_pause;
    char key_enter;
    char key_teleport;
    char key_wall;
    char key_empty;
    Term::RGB snake_color;
    Term::RGB empty_color;
    Term::RGB wall_color;
    Term::RGB teleport_color;
    Term::RGB bonus_color;
    Term::RGB antibonus_color;
    Term::RGB speed_bonus_color;
    Term::RGB speed_antibonus_color;
};

int parser(Settings &settings, std::string &filename);

void replace_setting(std::string, std::string, unsigned);
void replace_float_setting(std::string, std::string, float);
void replace_char_setting(std::string, std::string, char);
void replace_rgb_setting(std::string, std::string, Term::RGB);
void copy_file(std::string, std::string);
