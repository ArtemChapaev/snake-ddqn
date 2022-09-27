#pragma once
 
#include "snake.h"
 
class Control {
    /// Абстрактный класс управления, который хранит чистый виртуальный метод смены направление движения змеи.
public:
    virtual Direction read_direction(Direction) = 0;
    bool check_direction(Direction last_dir, Direction new_dir);
};
