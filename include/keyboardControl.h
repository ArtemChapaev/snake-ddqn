#pragma once

#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#include <iostream>

#include "control.h"
#include "settings.h"
#include "snake.h"

class KeyboardControl : public Control {
    /// A descendant of the abstract control class Control, which implements control by pressing keys.
    /// The class also stores game keys.
   public:
    KeyboardControl(Settings);
    ~KeyboardControl();

    Keys read_key(Keys);
    int read_sym();

    unsigned read_option();
    float read_float_option();
    char read_char_option();

   private:
    void enable_specific_enter();
    void disable_specific_enter();

    const char up;
    const char left;
    const char down;
    const char right;
    const char pause;
    const char enter;
    const char teleport;
    const char wall;
    const char empty;
    const int original_flags;
    struct termios savetty;
};
