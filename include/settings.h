#pragma once

struct Settings {
    Settings(unsigned mL = 20, unsigned mW = 20, float sp = 1, bool sW = 0, bool sc = 0, bool r = 0, bool bA = 0,
             unsigned vM = 1) :
            map_length(mL), map_width(mW), speed(sp), solid_wall(sW), score(sc), record(r), bonus_apples(bA),
            view_mode(vM) {};

    unsigned map_length;
    unsigned map_width;
    float speed;
    bool solid_wall;
    bool score;
    bool record;
    bool bonus_apples;
    unsigned view_mode;
};
