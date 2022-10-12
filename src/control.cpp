#include "control.h"

bool Control::check_direction(Keys last_dir, Keys new_dir) {
    if (last_dir - new_dir == 2 || last_dir - new_dir == -2) {
        return false;
    }
    return true;
}
