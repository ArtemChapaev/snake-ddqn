#pragma once

class ConsoleUI {
public:
    void clear_display();
    void clear_line();
    void set_cursor(unsigned, unsigned);

    unsigned comax();
    unsigned romax();
};
