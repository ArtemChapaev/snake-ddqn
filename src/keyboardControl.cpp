#include "keyboardControl.h"

KeyboardControl::KeyboardControl(Settings settings) : up(settings.key_up), left(settings.key_left),
                                                      down(settings.key_down), right(settings.key_right),
                                                      pause(settings.key_pause), enter(settings.key_enter),
                                                      teleport(settings.key_teleport), wall(settings.key_wall),
                                                      empty(settings.key_empty), original_flags(fcntl(0, F_GETFL)) {
    enable_specific_enter();
}

KeyboardControl::~KeyboardControl() {
    disable_specific_enter();
}

void KeyboardControl::enable_specific_enter() {
    fcntl(0, F_SETFL, original_flags | O_NONBLOCK);

    struct termios tty;
    tcgetattr(0, &tty);
    savetty = tty;
    tty.c_lflag &= ~(ICANON | ECHO | ISIG);
    tty.c_cc[VMIN] = 1;
    tcsetattr(0, TCSAFLUSH, &tty);
}

void KeyboardControl::disable_specific_enter() {
    fcntl(0, F_SETFL, original_flags);

    tcsetattr(0, TCSAFLUSH, &savetty);
}

Keys KeyboardControl::read_key(Keys last_dir) {
    int ch = read_sym();

    if (ch == 0) {
        return last_dir;
    } else if (ch == up) {
        return Keys::up;
    } else if (ch == right) {
        return Keys::right;
    } else if (ch == down) {
        return Keys::down;
    } else if (ch == left) {
        return Keys::left;
    } else if (ch == pause) {
        return Keys::interruption;
    } else if (ch == enter) {
        return Keys::enter;
    } else if (ch == teleport) {
        return Keys::teleport;
    } else if (ch == wall) {
        return Keys::wall;
    } else if (ch == empty) {
        return Keys::empty;
    } else {
        return Keys::error;
    }
}

int KeyboardControl::read_option() {
    KeyboardControl::disable_specific_enter();

    int input;
    std::cin >> input;

    KeyboardControl::enable_specific_enter();

    return abs(input);
}

char KeyboardControl::read_char_option() {
    KeyboardControl::disable_specific_enter();

    int ch = read_sym();
    KeyboardControl::enable_specific_enter();

    if (ch == -2) {
        return 27;
    } else {
        return ch;
    }
}

float KeyboardControl::read_float_option() {
    KeyboardControl::disable_specific_enter();

    float input;
    std::cin >> input;

    KeyboardControl::enable_specific_enter();
    return std::abs(input);
}

Term::RGB KeyboardControl::read_rgb_option() {
    KeyboardControl::disable_specific_enter();

    std::string input;
    std::string r, g, b;
    Term::RGB color;

    getline(std::cin, r, ',');
    getline(std::cin, g, ',');
    getline(std::cin, b);

    color.r = static_cast<uint8_t>(stoi(r));
    color.g = static_cast<uint8_t>(stoi(g));
    color.b = static_cast<uint8_t>(stoi(b));

    KeyboardControl::enable_specific_enter();

    return color;
}

int KeyboardControl::read_sym() {
    char ch[1] = "";
    if (read(0, ch, 1) == 0) {
        return 0;
    }

    if (ch[0] == 27) {
        char ch_2[2];
        if (read(0, ch_2, 2) == 2) {
            switch (ch_2[1]) {
                case 'A':
                    return 72; // arrow up
                case 'D':
                    return 75; // arrow left
                case 'B':
                    return 80; // arrow down
                case 'C':
                    return 77; // arrow right
                default:
                    return -2; // error
            }
        }
    }
    return ch[0];
}
