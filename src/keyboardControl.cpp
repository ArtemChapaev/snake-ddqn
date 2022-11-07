#include "keyboardControl.h"

KeyboardControl::KeyboardControl(Settings settings) : up(settings.key_up), left(settings.key_left),
                                                      down(settings.key_down), right(settings.key_right),
                                                      pause(settings.key_pause), enter(settings.key_enter),
                                                      original_flags(fcntl(0, F_GETFL)) {
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

int KeyboardControl::read_option() {
    KeyboardControl::disable_specific_enter();
    
    int input;
    std::cin >> input;

    KeyboardControl::enable_specific_enter();
    return input;
}

char KeyboardControl::read_char_option() {
    KeyboardControl::disable_specific_enter();

    char ch[1];
    read(0, ch, 1);

    if (ch[0] == 27) {
        char ch_2[2];
        if (read(0, ch_2, 2) == 2) {
            KeyboardControl::enable_specific_enter();
            switch (ch_2[1]) {
                case 'A':
                    return 72; // arrow up
                case 'D':
                    return 75; // arrow left
                case 'B':
                    return 80; // arrow down
                case 'C':
                    return 77; // arrow right
                case 27:
                    return 27;
                case 10:
                    return 10;
            }
        }
    }

    KeyboardControl::enable_specific_enter();
    return ch[0];
}

float KeyboardControl::read_float_option() {
    KeyboardControl::disable_specific_enter();

    float input;
    std::cin >> input;

    KeyboardControl::enable_specific_enter();
    return input;
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

Keys KeyboardControl::read_key(Keys last_dir) {
    char ch[1];
    if (read(0, ch, 1) <= 0) {
        return last_dir;
    } else if (ch[0] == 27) {
        char ch_2[2];

        if (read(0, ch_2, 2) == 2) {
            switch (ch_2[1]) {
                case 'A':
                    ch[0] = 72; // arrow up
                    break;
                case 'D':
                    ch[0] = 75; // arrow left
                    break;
                case 'B':
                    ch[0] = 80; // arrow down
                    break;
                case 'C':
                    ch[0] = 77; // arrow right
                    break;
                default:
                    return Keys::error;
            }
        }
    }

    if (ch[0] == up) {
        return Keys::up;
    } else if (ch[0] == right) {
        return Keys::right;
    } else if (ch[0] == down) {
        return Keys::down;
    } else if (ch[0] == left) {
        return Keys::left;
    } else if (ch[0] == pause) {
        return Keys::interruption;
    } else if (ch[0] == enter) {
        return Keys::enter;
    }
    return Keys::error;
}
