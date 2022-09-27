#include "consoleUI.h"

void ConsoleUI::clear_display() {
    std::cout << "\033[2J";
}

void ConsoleUI::clear_line() {
    std::cout << "\033[K";
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
