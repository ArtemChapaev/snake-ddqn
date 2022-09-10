#pragma once

#include "snake.h"

class Control {
public:
    Control(char up = 72, char right = 77, char down = 80, char left = 75) : up(up), right(right),
                                                                             down(down), left(left) {}

    Direction read_direction(Direction);
    bool check_direction(Direction last_dir, Direction new_dir);
    int enable_noncanonical_input(struct termios &);
    void disable_noncanonical_input(struct termios &);
    void enable_nonblock_input(int);
    void disable_nonblock_input(int);

private:
    char up;
    char right;
    char down;
    char left;
};
