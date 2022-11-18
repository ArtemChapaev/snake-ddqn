#pragma once

#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fcntl.h>
#include <memory>
#include <termios.h>
#include <stack>
#include <string>
#include <unistd.h>
#include <vector>

#include "consoleUI.h"
#include "control.h"
#include "keyboardControl.h"
#include "mapModel.h"
#include "mapView.h"
#include "menu.h"
#include "settings.h"
#include "snake.h"

#define LEVEL_SPEED(level_number) (1. + level_number * 0.15)

const unsigned kBonusesForNewLevel = 5;
const unsigned kMovesForSpeedBonus = 15;
const unsigned kMovesAfterControlError = 6;

const unsigned kLevelPause = 1500000;
const unsigned kMovePause = 300000;
const unsigned kGamePause = 1000000;

const double kBonusSpeedForSnake = 1.5;

const unsigned kPlaytimeStringLength = 20;
const unsigned kHighscoreStringLength = 16;
const unsigned kFinalscoreStringLength = 13;

const std::string kWinString = "LEVEL UP!";
const std::string kLeaderboardFile = "leaderboard.txt";

class Game {
    /// A controller class that connects the model and the display of the game.
    /// Through this class, you can run the game itself.
public:
    explicit Game(std::string file = "settings.txt");
    ~Game();

    int start_game(bool);
    int start_level(unsigned);
    int pause_game();
    int print_deathscreen();
    int write_to_leaderboard();
    void print_control_error_screen();

private:
    std::string filename;
    Settings settings;
    unsigned highest_score;
    unsigned death_score;
    std::clock_t game_time;
    std::clock_t pause_time;
};
