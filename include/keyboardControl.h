#pragma once

#include <fcntl.h>
#include <iostream>
#include <termios.h>
#include <unistd.h>

#include "control.h"
#include "settings.h"
#include "snake.h"

class KeyboardControl : public Control {
    /// Потомок абстрактного класса управления Control, реализующий управление с помощью нажатия клавиш.
    /// Также класс хранит игровые клавиши, которые можно менять.
public:
    KeyboardControl(Settings);
    ~KeyboardControl();
    Keys read_key(Keys last_dir) override;

private:
    const char up;
    const char left;
    const char down;
    const char right;
    const char pause;
    const int original_flags;
    struct termios savetty;
};
