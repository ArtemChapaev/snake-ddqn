#pragma once

#include "control.h"

class KeyboardControl : public Control {
public:
    KeyboardControl(char up = 72, char left = 75, char down = 80, char right = 77);
    ~KeyboardControl();
    Direction read_direction(Direction) override;

private:
    int original_flags;
    struct termios savetty;
};
