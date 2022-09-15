#include <cstring>

#include "game.h"
#include "settings.h"

int main(int argc, char **argv) {
    bool random_apples = true;
    if (argc > 1 && !strcmp(argv[1], "-a")) {
        random_apples = false;
    }
    Settings settings;
    Game game(settings);
    game.start_game(random_apples);
}
