#pragma once

// #include <string>

#include "settings.h"

class Game {
public:
    Game(Settings);
//    int launcher();

    int start_game();

//    int game_over();
private:
//    std::string filename;
    Settings settings;
};
