#pragma once

#include "control.h"
#include "settings.h"
#include "snake.h"

class aiControl : public Control {
   public:
    Keys get_direction(unsigned, unsigned, unsigned, unsigned);
};