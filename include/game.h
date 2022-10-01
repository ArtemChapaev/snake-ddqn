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

#define LEVEL_SPEED(level_number) (1. + level_number * 0.1)

const unsigned BONUSES_FOR_NEW_LEVEL = 8;
const unsigned MOVES_FOR_SPEED_BONUS = 10;

const unsigned LEVEL_PAUSE = 1500000;
const unsigned MOVE_PAUSE = 300000;

const double BONUS_SPEED_FOR_SNAKE = 1.5;

class Game {
    /// Класс-контроллер, который связывает модель и отображение игры.
    /// Через этот класс можно запустить саму игру.
public:
    Game();
//    int launcher();

    int start_game(bool);
    bool start_level(unsigned);
    int deathscreen();

//    int game_over();
private:
//    std::string filename;
    Settings settings;
    unsigned highest_score;
    unsigned death_score;
    std::clock_t game_time;
};
