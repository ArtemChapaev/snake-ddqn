#include "keyboardControl.h"

KeyboardControl::KeyboardControl(Settings settings) : up(settings.key_up), left(settings.key_left),
                                                      down(settings.key_down), right(settings.key_right),
                                                      pause(settings.key_pause), original_flags(fcntl(0, F_GETFL)) {
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
    } else if ((int) ch[0] == 27) {
        char ch_2[2];

        if (read(0, ch_2, 2) == 2) {
            switch (ch_2[1]) {
                case 'A':
                    ch[0] = 72;
                    break;
                case 'D':
                    ch[0] = 75;
                    break;
                case 'B':
                    ch[0] = 80;
                    break;
                case 'C':
                    ch[0] = 77;
                    break;
            }
        } else {
            ch[0] = 27;
        }
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
    } else if (ch[0] == pause) {
        // implement
    }
    return dir;
}
