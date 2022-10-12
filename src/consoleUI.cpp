#include "consoleUI.h"

void ConsoleUI::clear_full_display() {
    set_cursor(1, 1);
    for (unsigned j = 1; j <= romax(); ++j) {
        for (unsigned i = 1; i <= comax(); ++i) {
            std::cout << ' ';
        }
        std::cout << std::endl;
    }
    set_cursor(1, 1);
}

void ConsoleUI::clear_game_field(Settings settings) {
    for (unsigned j = 1; j <= settings.map_width + 1; ++j) { // +1 bcs score calculating
        for (unsigned i = 1; i <= settings.map_length; ++i) {
            set_cursor(i, j);
            std::cout << ' ';
        }
    }
    set_cursor(1, 1);
}

void ConsoleUI::set_cursor(unsigned x, unsigned y) {
    std::cout << "\033[" << x << ";" << y << "H";
}

unsigned ConsoleUI::comax() {
    struct winsize ww;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ww);
    return ww.ws_col;
}

unsigned ConsoleUI::romax() {
    struct winsize ww;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ww);
    return ww.ws_row;
}
