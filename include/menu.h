#pragma once

#include <cstring>
#include <iostream>
#include <memory>
#include <stack>
#include <unistd.h>

#include "consoleUI.h"
#include "game.h"
#include "keyboardControl.h"
#include "settings.h"

#define SLEEP_TIME 200

class Menu {
    /// Abstract class for menu, all menu types inherit from it
public:
    explicit Menu(std::string file);
    virtual void pure_draw() = 0; /// draws pure menu without option selection (without underlines)
    virtual void draw(int) = 0; /// after pure_draw() call draws selected underlined string
    virtual unsigned update(int &, std::stack<std::unique_ptr<Menu>> &) = 0; /// handles clicks
    virtual void print_logo() = 0;
protected:
    std::string filename;
    Settings settings;
};

class MainMenu : public Menu
{
public:
    explicit MainMenu(std::string file);
    void pure_draw() override;
    void draw(int) override;
    unsigned update(int &, std::stack<std::unique_ptr<Menu>> &) override;
    void print_logo() override;
private:
    enum options { start, leaderboard, setings, credits, exit };
    unsigned options_count;
};

class LeaderboardMenu : public Menu 
{
public:
    explicit LeaderboardMenu(std::string file);
    void pure_draw() override;
    void draw(int) override;
    unsigned update(int &, std::stack<std::unique_ptr<Menu>> &) override;
    void print_logo() override;
private:
    enum options { tbu, exit };
    unsigned options_count;
};

class SettingsGeneralMenu : public Menu 
{
public:
    explicit SettingsGeneralMenu(std::string file);
    void pure_draw() override;
    void draw(int) override;
    unsigned update(int &, std::stack<std::unique_ptr<Menu>> &) override;
    void print_logo() override;
private:
    enum options { snake, map, graphic, control, exit };
    unsigned options_count;
};

class SettingsSnakeMenu : public Menu 
{
public:
    explicit SettingsSnakeMenu(std::string file);
    void pure_draw() override;
    void draw(int) override;
    unsigned update(int &, std::stack<std::unique_ptr<Menu>> &) override;
    void print_logo() override;
private:
    enum options { speed, reset_length, exit };
    unsigned options_count;
};

class SettingsMapMenu : public Menu 
{
public:
    explicit SettingsMapMenu(std::string file);
    void pure_draw() override;
    void draw(int) override;
    unsigned update(int &, std::stack<std::unique_ptr<Menu>> &) override;
    void print_logo() override;
private:
    enum options { length, width, solid_walls, bonus_apples, teleports, show_score, exit};
    unsigned options_count;
};

class SettingsGraphicMenu : public Menu 
{
public:
    explicit SettingsGraphicMenu(std::string file);
    void pure_draw() override;
    void draw(int) override;
    unsigned update(int &, std::stack<std::unique_ptr<Menu>> &) override;
    void print_logo() override;
private:
    enum options { snake, empty_block, wall, teleport, bonus, anti_bonus, speed_bonus,
                    anti_speed_bonus, exit};
    unsigned options_count;
};

class SettingsControlMenu : public Menu 
{
public:
    explicit SettingsControlMenu(std::string file);
    void pure_draw() override;
    void draw(int) override;
    unsigned update(int &, std::stack<std::unique_ptr<Menu>> &) override;
    void print_logo() override;
private:
    enum options { up, down, left, rightt, pause, enter, exit };
    unsigned options_count;
};

class TitlesMenu : public Menu {
public:
    explicit TitlesMenu(std::string file);
    void pure_draw() override;
    void draw(int) override;
    unsigned update(int &, std::stack<std::unique_ptr<Menu>> &) override;
    void print_logo() override;
};