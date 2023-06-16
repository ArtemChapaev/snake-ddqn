#pragma once

#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#include <chrono>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <stack>
#include <string>
#include <vector>

#include "aiControl.h"
#include "consoleUI.h"
#include "control.h"
#include "keyboardControl.h"
#include "mapModel.h"
#include "mapView.h"
#include "menu.h"
#include "settings.h"
#include "snake.h"

#define LEVEL_SPEED(level_number) (1. + level_number * 0.1)
#define LAYERS 28, 16, 4

const unsigned kBonusesForNewLevel = 5;
const unsigned kMovesForSpeedBonus = 15;
const unsigned kMovesAfterControlError = 6;

const unsigned kLevelPause = 1500000;
const unsigned kMovePause = 300000;

const double kBonusSpeedForSnake = 1.5;

const unsigned kPlayTimeStringLength = 20;
const unsigned kHighScoreStringLength = 16;
const unsigned kFinalScoreStringLength = 13;

const std::string kWinString = "LEVEL UP!";
const std::string kLeaderboardFile = "leaderboard.txt";

// subject to change into doubles
const double kRewardPositive = 1;
const double kRewardNegative = -1;

const unsigned kEpisodesForOutput = 50;
const unsigned kEpisodesForSaveHyperparams = 100;

class Game {
    /// A controller class that connects the model and the display of the game.
    /// Through this class, you can run the game itself.
   public:
    explicit Game(std::string file = "settings.txt");
    ~Game();

    int start_game(bool);

    int start_level(unsigned);
    int start_ai_learning(unsigned);
    int start_ai_game(unsigned);

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
