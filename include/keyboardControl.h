#pragma once

#include <fcntl.h>
#include <iostream>
#include <termios.h>
#include <unistd.h>

#include "control.h"
#include "snake.h"

class KeyboardControl : public Control {
    /// Потомок абстрактного класса управления Control, реализующий управление с помощью нажатия клавиш.
    /// Также класс хранит игровые клавиши, которые можно менять.
public:
    KeyboardControl(char up = 72, char left = 75, char down = 80, char right = 77);
    ~KeyboardControl();
    Direction read_direction(Direction) override;

private:
    char up;
    char left;
    char down;
    char right;
    int original_flags;
    struct termios savetty;
};
