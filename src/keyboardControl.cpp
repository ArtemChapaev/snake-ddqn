#include "keyboardControl.h"

KeyboardControl::KeyboardControl(char up, char left, char down, char right) : up(up), left(left), down(down),
                                                                              right(right),
                                                                              original_flags(fcntl(0, F_GETFL)) {
    fcntl(0, F_SETFL, original_flags | O_NONBLOCK);

    struct termios tty;
    tcgetattr(0, &tty);
    savetty = tty;
    tty.c_lflag &= ~(ICANON | ECHO | ISIG);
    tty.c_cc[VMIN] = 1;
    tcsetattr(0, TCSAFLUSH, &tty);
}

KeyboardControl::~KeyboardControl() {
    fcntl(0, F_SETFL, original_flags);

    tcsetattr(0, TCSAFLUSH, &savetty);
}

Direction KeyboardControl::read_direction(Direction last_dir) {
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
