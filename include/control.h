#pragma once

#include "snake.h"

class Control {
    /// An abstract control class
   public:
    bool check_direction(Keys, Keys);

   protected:
    Control() {}
};
