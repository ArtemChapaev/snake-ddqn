#include "control.h"

#include "snake.h"

Control::Control(char up, char left, char down, char right) : up(up), left(left), down(down), right(right) {}

bool Control::check_direction(Direction last_dir, Direction new_dir) {
    if (last_dir - new_dir == 2 || last_dir - new_dir == -2) {
        return false;
    }
    return true;
}
