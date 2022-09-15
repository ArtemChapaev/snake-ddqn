#pragma once

#include "snake.h"

class Control {
public:
    Control(char up, char left, char down, char right);
    virtual Direction read_direction(Direction) = 0;
    bool check_direction(Direction last_dir, Direction new_dir);

protected:
    char up;
    char right;
    char down;
    char left;
};
