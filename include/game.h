#pragma once

#include <cstdlib>
#include <ctime>
#include <fcntl.h>
#include <termios.h>
// #include <string>
#include <unistd.h>

#include "consoleUI.h"
#include "control.h"
#include "keyboardControl.h"
#include "mapModel.h"
#include "mapView.h"
#include "settings.h"
#include "snake.h"

class Game {
    /// Класс-контроллер, который связывает модель и отображение игры.
    /// Через этот класс можно запустить саму игру.
public:
    Game(Settings);
//    int launcher();

    int start_game(bool);
    int deathscreen();

//    int game_over();
private:
//    std::string filename;
    Settings settings;
    int highest_score;
    int death_score;
    clock_t game_time;
};
