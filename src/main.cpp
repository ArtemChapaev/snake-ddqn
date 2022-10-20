#include <cstring>

#include "game.h"

int main(int argc, char **argv) {
    bool random_apples = true;
    std::string filename = "settings.txt";

    if (argc == 2 && !strcmp(argv[1], "-a")) {
        random_apples = false;
    } else {
        for (int i = 0; i < argc; ++i)
            if (!strcmp(argv[i], "-a")) {
                random_apples = false;
            } else if (!strcmp(argv[i], "-f") && i + 1 < argc) {
                filename = argv[i + 1];
            }
    }

    std::cout << "\033[2J"; // clear of screen
    Game game(filename);
    game.start_game(random_apples);
    game.print_deathscreen();
}
