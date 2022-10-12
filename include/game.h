#pragma once

#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fcntl.h>
#include <termios.h>
#include <string>
#include <unistd.h>

#include "consoleUI.h"
#include "control.h"
#include "keyboardControl.h"
#include "mapModel.h"
#include "mapView.h"
#include "settings.h"
#include "snake.h"

#define LEVEL_SPEED(level_number) (1. + level_number * 0.15)

const unsigned BONUSES_FOR_NEW_LEVEL = 5;
const unsigned MOVES_FOR_SPEED_BONUS = 10;

const unsigned LEVEL_PAUSE = 1500000;
const unsigned MOVE_PAUSE = 300000;
const unsigned GAME_PAUSE = 1000000;

const double BONUS_SPEED_FOR_SNAKE = 1.5;

const std::string WIN_STRING = "LEVEL UP!";

class Game {
    /// Класс-контроллер, который связывает модель и отображение игры.
    /// Через этот класс можно запустить саму игру.
public:
    explicit Game(std::string file = "settings.txt");
    int start_game(bool);
    bool start_level(unsigned);
    int print_deathscreen();

private:
    std::string filename;
    Settings settings;
    unsigned highest_score;
    unsigned death_score;
    std::clock_t game_time;
};
