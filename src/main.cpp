#include "game.h"
#include "settings.h"

int main() {
    Settings settings;
    Game game(settings);
    game.start_game();
}
