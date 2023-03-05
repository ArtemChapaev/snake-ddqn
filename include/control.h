#pragma once

#include "snake.h"

class Control {
    /// An abstract control class that stores a pure virtual method for changing the direction of the snake's
    /// movement.
   public:
    virtual Keys read_key(Keys) = 0;
    bool check_direction(Keys, Keys);
};
