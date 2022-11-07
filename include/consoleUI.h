#pragma once

#include <iostream>
#include <sys/ioctl.h>
#include <sstream>
#include <unistd.h>

#include "settings.h"

class ConsoleUI {
    /// A class that interacts with the console using escape sequences.
public:
    void clear_full_display();
    void clear_line(unsigned);
    void clear_game_field(Settings);
    void underline();
    void print_rgb(unsigned, unsigned, unsigned);
    static void reset();

    static void set_cursor(unsigned, unsigned);
    static void highlight(unsigned);
    static void off_cursor();
    static void on_cursor();

    unsigned comax();
    unsigned romax();
};
