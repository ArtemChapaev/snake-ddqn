#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "cpp-terminal/base.hpp"

struct Settings {
    Settings(unsigned mL = 20, unsigned mW = 20, float sp = 1, bool sW = 0, bool sc = 1, bool bA = 1,
             unsigned vM = 2, bool rL = 0, char kU = 72, char kD = 80, char kR = 77, char kL = 75,
             char kP = 27, char kEn = 10, char kT = 116, char kW = 119, char kEm = 101, unsigned aM = 0,

             Term::Color4 sC = Term::Color4::GREEN, Term::Color4 eC = Term::Color4::BLACK,
             Term::Color4 wC = Term::Color4::GRAY, Term::Color4 tC = Term::Color4::WHITE_BRIGHT,
             Term::Color4 bC = Term::Color4::RED, Term::Color4 aC = Term::Color4::YELLOW,
             Term::Color4 sbC = Term::Color4::BLUE, Term::Color4 saC = Term::Color4::MAGENTA)
        :

          map_length(mL),
          map_width(mW),
          speed(sp),
          solid_wall(sW),
          score(sc),
          bonus_apples(bA),
          view_mode(vM),
          reset_length(rL),
          key_up(kU),
          key_down(kD),
          key_right(kR),
          key_left(kL),
          key_pause(kP),
          key_enter(kEn),
          key_teleport(kT),
          key_wall(kW),
          key_empty(kEm),
          ai_mode(aM),

          snake_color(sC),
          empty_color(eC),
          wall_color(wC),
          teleport_color(tC),
          bonus_color(bC),
          antibonus_color(aC),
          speed_bonus_color(sbC),
          speed_antibonus_color(saC){};

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
    unsigned ai_mode;
    Term::Color4 snake_color;
    Term::Color4 empty_color;
    Term::Color4 wall_color;
    Term::Color4 teleport_color;
    Term::Color4 bonus_color;
    Term::Color4 antibonus_color;
    Term::Color4 speed_bonus_color;
    Term::Color4 speed_antibonus_color;
};

int parser(Settings &settings, std::string &filename);

void replace_setting(std::string, std::string, unsigned);
void replace_float_setting(std::string, std::string, float);
void replace_char_setting(std::string, std::string, char);
void replace_rgb_setting(std::string, std::string, Term::RGB);
void copy_file(std::string, std::string);
