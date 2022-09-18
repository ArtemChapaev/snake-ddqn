#pragma once

struct Settings {
    Settings(unsigned mL = 15, unsigned mW = 15, bool sW = 0, float sp = 1, bool sc = 0, bool r = 0, bool bA = 0, unsigned vm = 0) :
            map_length(mL), map_width(mW), solid_wall(sW), speed(sp), score(sc), record(r), bonus_apples(bA), view_mode(vm) {};

    unsigned map_length;
    unsigned map_width;
    bool solid_wall;
    float speed;
    bool score;
    bool record;
    bool bonus_apples;
    unsigned view_mode;
};
