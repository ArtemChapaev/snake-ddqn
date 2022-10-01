#include <cstring>

#include "game.h"

int main(int argc, char **argv) {
    bool random_apples = true;
    if (argc > 1 && !strcmp(argv[1], "-a")) {
        random_apples = false;
    }
    Game game;
    game.start_game(random_apples);
    game.deathscreen();
}
