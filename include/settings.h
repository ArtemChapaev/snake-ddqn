#pragma once

#include <fstream>
#include <iostream>
#include <string>

struct Settings {
// Структура под настройки
    Settings(unsigned mL = 20, unsigned mW = 20, float sp = 1, bool sW = 1, bool sc = 1, bool bA = 1, bool te = 0,
             unsigned vM = 1, char kU = 72, char kD = 80, char kR = 77, char kL = 75, char kP = 27) :
            map_length(mL), map_width(mW), speed(sp), solid_wall(sW), score(sc), bonus_apples(bA),
            teleport(te), view_mode(vM), key_up(kU), key_down(kD), key_right(kR), key_left(kL), key_pause(kP) {};

    unsigned map_length;
    unsigned map_width;
    float speed;
    bool solid_wall;
    bool score;
    bool bonus_apples;
    bool teleport;
    unsigned view_mode;
    char key_up;
    char key_down;
    char key_right;
    char key_left;
    char key_pause;
};

// Объявление функции парсер
int parser(Settings &settings);