#pragma once

#include <unistd.h>

#include <cstring>
#include <iostream>
#include <memory>
#include <stack>

#include "consoleUI.h"
#include "game.h"
#include "keyboardControl.h"
#include "settings.h"

const unsigned kSleepTime = 200;

class Menu {
    /// Abstract class for menu, all menu types inherit from it
   public:
    explicit Menu(std::string);
    virtual void draw(unsigned) = 0;  // after pure_draw() call draws selected underlined string
    virtual unsigned update(unsigned &, std::stack<std::unique_ptr<Menu>> &) = 0;  // handles clicks
    virtual ~Menu() = default;

   protected:
    virtual void pure_draw() = 0;  // draws pure menu without option selection (without underlines)
    virtual void print_logo() = 0;
    void print_cell_info(unsigned, Graphics *);  // draws info from conveyed string

    std::string filename;
    Settings game_settings;
};

class MainMenu : public Menu {
   public:
    MainMenu(std::string, bool);
    void draw(unsigned) override;
    unsigned update(unsigned &, std::stack<std::unique_ptr<Menu>> &) override;

   private:
    void pure_draw() override;
    void print_logo() override;

    enum options { start, leaderboard, settings, information, credits, exit };
    const unsigned options_count;
    const bool random_apples;
};

class PauseMenu : public Menu {
   public:
    explicit PauseMenu(std::string);
    void draw(unsigned) override;
    unsigned update(unsigned &, std::stack<std::unique_ptr<Menu>> &) override;
    enum pause_exit_codes { resume_code = 1, restart_code, exit_code };

   private:
    void pure_draw() override;
    void print_logo() override;

    enum options { resume, restart, information, exit };
    const unsigned options_count;
};

class LeaderboardMenu : public Menu {
   public:
    explicit LeaderboardMenu(std::string);
    void draw(unsigned) override;
    unsigned update(unsigned &, std::stack<std::unique_ptr<Menu>> &) override;

   private:
    void pure_draw() override;
    void print_logo() override;

    enum options { tbu, exit };
    const unsigned options_count;
};

class SettingsGeneralMenu : public Menu {
   public:
    explicit SettingsGeneralMenu(std::string);
    void draw(unsigned) override;
    unsigned update(unsigned &, std::stack<std::unique_ptr<Menu>> &) override;

   private:
    void pure_draw() override;
    void print_logo() override;

    enum options { snake, map, graphic, control, save_sets, exit };
    const unsigned options_count;
};

class SettingsSnakeMenu : public Menu {
   public:
    explicit SettingsSnakeMenu(std::string);
    void draw(unsigned) override;
    unsigned update(unsigned &, std::stack<std::unique_ptr<Menu>> &) override;

   private:
    void pure_draw() override;
    void print_logo() override;

    enum options { ai_mode, speed, reset_length, epochs, exit };
    const unsigned options_count;
};

class SettingsMapMenu : public Menu {
   public:
    explicit SettingsMapMenu(std::string);
    void draw(unsigned) override;
    unsigned update(unsigned &, std::stack<std::unique_ptr<Menu>> &) override;

   private:
    void pure_draw() override;
    void print_logo() override;

    enum options { length, width, solid_walls, bonus_apples, show_score, custom_map, exit };
    const unsigned options_count;
};

class SettingsGraphicMenu : public Menu {
   public:
    explicit SettingsGraphicMenu(std::string);
    void draw(unsigned) override;
    unsigned update(unsigned &, std::stack<std::unique_ptr<Menu>> &) override;

   private:
    unsigned convert_color_number(unsigned);
    void pure_draw() override;
    void print_logo() override;

    enum options {
        mode,
        colors,
        snake,
        empty_block,
        wall,
        teleport,
        bonus,
        antibonus,
        speed_bonus,
        speed_antibonus,
        exit
    };
    const unsigned options_count;
};

class SettingsControlMenu : public Menu {
   public:
    explicit SettingsControlMenu(std::string);
    void draw(unsigned) override;
    unsigned update(unsigned &, std::stack<std::unique_ptr<Menu>> &) override;

   private:
    void pure_draw() override;
    void print_logo() override;
    void print_key(char);

    enum options { up, down, left, right, pause, enter, teleport, wall, empty, exit };
    const unsigned options_count;
};

class SavedSettingsMenu : public Menu {
   public:
    explicit SavedSettingsMenu(std::string);
    void draw(unsigned) override;
    unsigned update(unsigned &, std::stack<std::unique_ptr<Menu>> &) override;

   private:
    void pure_draw() override;
    void print_logo() override;

    enum options { save1, save2, save3, read1, read2, read3, exit };
    const unsigned options_count;
};

class CustomMapSettingsMenu : public Menu {
   public:
    explicit CustomMapSettingsMenu(std::string);
    void draw(unsigned) override;
    unsigned update(unsigned &, std::stack<std::unique_ptr<Menu>> &) override;

   private:
    void pure_draw() override;
    void print_logo() override;

    MapModel map_model;
    MapView map_view;
    unsigned i;
    unsigned j;
};

class ColorsMenu : public Menu {
   public:
    explicit ColorsMenu(std::string);
    void draw(unsigned) override;
    unsigned update(unsigned &, std::stack<std::unique_ptr<Menu>> &) override;

   private:
    void pure_draw() override;
    void print_logo() override;
};

class TitlesMenu : public Menu {
   public:
    explicit TitlesMenu(std::string);
    void draw(unsigned) override;
    unsigned update(unsigned &, std::stack<std::unique_ptr<Menu>> &) override;

   private:
    void pure_draw() override;
    void print_logo() override;
};

class GameInformationMenu : public Menu {
   public:
    explicit GameInformationMenu(std::string);
    void draw(unsigned) override;
    unsigned update(unsigned &, std::stack<std::unique_ptr<Menu>> &) override;

   private:
    void pure_draw() override;
    void print_logo() override;
};
