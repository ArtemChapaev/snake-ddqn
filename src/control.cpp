#include "control.h"

bool Control::check_direction(Direction last_dir, Direction new_dir) {
    if (last_dir - new_dir == 2 || last_dir - new_dir == -2) {
        return false;
    }
    return true;
}
