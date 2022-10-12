#pragma once
 
#include "snake.h"
 
class Control {
    /// Абстрактный класс управления, который хранит чистый виртуальный метод смены направление движения змеи.
public:
    virtual Keys read_key(Keys) = 0;
    bool check_direction(Keys last_dir, Keys new_dir);
};
