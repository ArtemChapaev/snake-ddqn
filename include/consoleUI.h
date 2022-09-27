#pragma once

#include <iostream>
#include <sys/ioctl.h>
#include <sstream>
#include <unistd.h>

class ConsoleUI {
    /// Класс, который взаимодействует с консолью используя эскейп-последовательности
public:
    void clear_display();
    void clear_line();
    void set_cursor(unsigned, unsigned);

    unsigned comax();
    unsigned romax();
};
