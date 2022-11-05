#pragma once

#include <fcntl.h>
#include <iostream>
#include <termios.h>
#include <unistd.h>

#include "control.h"
#include "settings.h"
#include "snake.h"

class KeyboardControl : public Control {
    /// A descendant of the abstract control class Control, which implements control by pressing keys.
    /// The class also stores game keys.
public:
    KeyboardControl(Settings);
    ~KeyboardControl();

    Keys read_key(Keys) override;

private:
    void enable_specific_enter();
    void disable_specific_enter();
    const char up;
    const char left;
    const char down;
    const char right;
    const char pause;
    const char enter;
    const int original_flags;
    struct termios savetty;
};
