#include <fcntl.h>
#include <iostream>
#include <termios.h>
#include <unistd.h>

#include "control.h"
#include "snake.h"

Control::Control(char up, char right, char down, char left): up(up), right(right), down(down), left(left) {}

int Control::enable_noncanonical_input(struct termios &savetty) {
    if (!isatty(0)) {
        return 1;
    }

    struct termios tty;

    tcgetattr(0, &tty);
    savetty = tty;
    tty.c_lflag &= ~(ICANON | ECHO | ISIG);
    tty.c_cc[VMIN] = 1;
    tcsetattr(0, TCSAFLUSH, &tty);
    return 0;
}

void Control::disable_noncanonical_input(struct termios &savetty) {
    tcsetattr(0, TCSAFLUSH, &savetty);
}

void Control::enable_nonblock_input(int flags) {
    fcntl(0, F_SETFL, flags | O_NONBLOCK);
}

void Control::disable_nonblock_input(int flags) {
    fcntl(0, F_SETFL, flags);
}

Direction Control::read_direction(Direction last_dir) {
    char ch[1];
    if (read(0, ch, 1) <= 0) {
        return last_dir;
    }

    Direction dir = last_dir;
    if (ch[0] == up) {
        dir = Direction::up;
    } else if (ch[0] == right) {
        dir = Direction::right;
    } else if (ch[0] == down) {
        dir = Direction::down;
    } else if (ch[0] == left) {
        dir = Direction::left;
    }
    return dir;
}

bool Control::check_direction(Direction last_dir, Direction new_dir) {
    if (last_dir - new_dir == 2 || last_dir - new_dir == -2) {
        return false;
    }
    return true;
}
