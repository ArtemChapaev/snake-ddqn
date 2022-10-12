#pragma once

#include <iostream>
#include <sys/ioctl.h>
#include <sstream>
#include <unistd.h>

#include "settings.h"

class ConsoleUI {
    /// Класс, который взаимодействует с консолью используя эскейп-последовательности
public:
    void clear_full_display();
    void clear_game_field(Settings);
    void set_cursor(unsigned, unsigned);

    unsigned comax();
    unsigned romax();

private:
};
