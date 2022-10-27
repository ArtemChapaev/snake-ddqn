#include "menu.h"

Menu::Menu(std::string file) : filename(file) {
    ConsoleUI::off_cursor();
    parser(game_settings, filename);
}

MainMenu::MainMenu(std::string file, bool random_apples) : Menu(file), options_count(exit),
                                                           random_apples(random_apples) {}

void MainMenu::pure_draw() {
    std::cout << "\033[17;33HStart game" << std::endl;
    std::cout << "\033[18;33HLeaderboard" << std::endl;
    std::cout << "\033[19;33HSettings" << std::endl;
    std::cout << "\033[20;33HCell information" << std::endl;
    std::cout << "\033[21;33HCredits" << std::endl;
    std::cout << "\033[22;33HExit" << std::endl;
}

void MainMenu::draw(unsigned string_num) {
    ConsoleUI::off_cursor();
    ConsoleUI console;
    console.clear_full_display();
    console.set_cursor(3, 1);

    print_logo();
    pure_draw();

    switch (string_num) {
        case start:
            std::cout << "\033[17;33H\033[4mStart game\033[0m" << std::endl;
            break;
        case leaderboard:
            std::cout << "\033[18;33H\033[4mLeaderboard\033[0m" << std::endl;
            break;
        case settings:
            std::cout << "\033[19;33H\033[4mSettings\033[0m" << std::endl;
            break;
        case information:
            std::cout << "\033[20;33H\033[4mCell information\033[0m" << std::endl;
            break;
        case credits:
            std::cout << "\033[21;33H\033[4mCredits\033[0m" << std::endl;
            break;
        case exit:
            std::cout << "\033[22;33H\033[4mExit\033[0m" << std::endl;
            break;
    }
}

unsigned MainMenu::update(unsigned &string_num, std::stack <std::unique_ptr<Menu>> &menus) {
    bool is_exit = false;
    KeyboardControl control(game_settings);

    while (!is_exit) {
        // initializes with right direction argument bcs there is no right direction option in menu
        Keys key = control.read_key(right);
        is_exit = true;
        switch (key) {
            case up:
                string_num > 0 ? string_num -= 1 : string_num = options_count;
                break;
            case down:
                string_num < options_count ? string_num += 1 : string_num = 0;
                break;
            case enter:
                if (string_num == start) {
                    int game_exit_code = 0;
                    do {
                        Game game(filename);
                        game_exit_code = game.start_game(random_apples);
                        game.print_deathscreen();
                        sleep(3);
                    } while (game_exit_code == PauseMenu::restart_code);

                    menus.top().get()->draw(string_num);
                } else if (string_num == leaderboard) {
                    string_num = 0;
                    Menu *m = new LeaderboardMenu(filename);
                    menus.push(std::unique_ptr<Menu>(m));
                    menus.top().get()->draw(string_num);
                } else if (string_num == settings) {
                    string_num = 0;
                    Menu *m = new SettingsGeneralMenu(filename);
                    menus.push(std::unique_ptr<Menu>(m));
                    menus.top().get()->draw(string_num);
                } else if (string_num == information) {
                    Menu *m = new GameInformationMenu(filename);
                    menus.push(std::unique_ptr<Menu>(m));
                    menus.top().get()->draw(string_num);
                } else if (string_num == credits) {
                    Menu *m = new TitlesMenu(filename);
                    menus.push(std::unique_ptr<Menu>(m));
                    menus.top().get()->draw(string_num);
                } else if (string_num == exit) {
                    ConsoleUI::on_cursor();
                    std::cout << "\033[1;1H";
                    std::cout << "\033[2J";
                    return 1;
                }
                break;
            default:
                is_exit = false;
                usleep(kSleepTime);
        }
    }
    return 0;
}

//************//


PauseMenu::PauseMenu(std::string file) : Menu(file), options_count(exit) {}

void PauseMenu::pure_draw() {
    std::cout << "\033[16;36HResume" << std::endl;
    std::cout << "\033[17;36HRestart" << std::endl;
    std::cout << "\033[18;36HSettings" << std::endl;
    std::cout << "\033[19;36HCell information" << std::endl;
    std::cout << "\033[20;36HExit" << std::endl;
}

void PauseMenu::draw(unsigned string_num) {
    ConsoleUI::off_cursor();
    ConsoleUI console;
    console.clear_full_display();
    console.set_cursor(3, 1);

    print_logo();
    pure_draw();

    switch (string_num) {
        case resume:
            std::cout << "\033[16;36H\033[4mResume\033[0m" << std::endl;
            break;
        case restart:
            std::cout << "\033[17;36H\033[4mRestart\033[0m" << std::endl;
            break;
        case settings:
            std::cout << "\033[18;36H\033[4mSettings\033[0m" << std::endl;
            break;
        case information:
            std::cout << "\033[19;36H\033[4mCell information\033[0m" << std::endl;
            break;
        case exit:
            std::cout << "\033[20;36H\033[4mExit\033[0m" << std::endl;
            break;
    }
}

unsigned PauseMenu::update(unsigned &string_num, std::stack <std::unique_ptr<Menu>> &menus) {
    bool is_exit = false;
    KeyboardControl control(game_settings);

    while (!is_exit) {
        Keys key = control.read_key(right);
        is_exit = true;
        switch (key) {
            case up:
                string_num > 0 ? string_num -= 1 : string_num = options_count;
                break;
            case down:
                string_num < options_count ? string_num += 1 : string_num = 0;
                break;
            case enter:
                if (string_num == settings) {
                    string_num = 0;
                    Menu *m = new SettingsGeneralMenu(filename);
                    menus.push(std::unique_ptr<Menu>(m));
                    menus.top().get()->draw(string_num);
                    break;
                }
                if (string_num == information) {
                    Menu *m = new GameInformationMenu(filename);
                    menus.push(std::unique_ptr<Menu>(m));
                    menus.top().get()->draw(string_num);
                    break;
                }
                if (string_num == resume) {
                    return resume_code;
                }
                if (string_num == restart) {
                    return restart_code;
                }
                if (string_num == exit) {
                    return exit_code;
                }
            default:
                is_exit = false;
                usleep(kSleepTime);
        }
    }
    return 0;
}

//************//


LeaderboardMenu::LeaderboardMenu(std::string file) : Menu(file), options_count(exit) {}

void LeaderboardMenu::pure_draw() {
    std::ifstream file(kLeaderboardFile);
    if (!file.good()) {
        std::cout << "\033[17;46HHistory is empty" << std::endl;
        std::cout << "\033[18;46HPress enter for exit" << std::endl;
        return;
    }
    unsigned string_num = 17;
    std::string data, score;
    while (!file.eof()) {
        getline(file, data, ';');
        if (data.empty()) {
            continue;
        }

        getline(file, score);
        std::cout << "\033[" << string_num++ << ";32H" << data << "\t|\t" << score << std::endl;
    }
    file.close();
    std::cout << "\033[" << string_num + 1 << ";32HPress enter for exit" << std::endl;
}

void LeaderboardMenu::draw(unsigned string_num) {
    ConsoleUI::off_cursor();
    ConsoleUI console;
    console.clear_full_display();
    console.set_cursor(3, 1);

    print_logo();
    pure_draw();
}

unsigned LeaderboardMenu::update(unsigned &string_num, std::stack <std::unique_ptr<Menu>> &menus) {
    bool is_exit = false;
    KeyboardControl control(game_settings);

    while (!is_exit) {
        Keys key = control.read_key(right);
        is_exit = true;

        switch (key) {
            case enter:
                string_num = 0;
                menus.pop();
                menus.top().get()->draw(string_num);
                break;
            default:
                is_exit = false;
                usleep(kSleepTime);
        }
    }
    return 0;
}

//************//


SettingsGeneralMenu::SettingsGeneralMenu(std::string file) : Menu(file), options_count(exit) {}

void SettingsGeneralMenu::pure_draw() {
    std::cout << "\033[17;46HSnake settings" << std::endl;
    std::cout << "\033[18;46HMap settings" << std::endl;
    std::cout << "\033[19;46HGraphic settings" << std::endl;
    std::cout << "\033[20;46HControl settings" << std::endl;
    std::cout << "\033[21;46HExit" << std::endl;
}

void SettingsGeneralMenu::draw(unsigned string_num) {
    ConsoleUI::off_cursor();
    ConsoleUI console;
    console.clear_full_display();
    console.set_cursor(3, 1);

    print_logo();
    pure_draw();

    switch (string_num) {
        case snake:
            std::cout << "\033[17;46H\033[4mSnake settings\033[0m" << std::endl;
            break;
        case map:
            std::cout << "\033[18;46H\033[4mMap settings\033[0m" << std::endl;
            break;
        case graphic:
            std::cout << "\033[19;46H\033[4mGraphic settings\033[0m" << std::endl;
            break;
        case control:
            std::cout << "\033[20;46H\033[4mControl settings\033[0m" << std::endl;
            break;
        case exit:
            std::cout << "\033[21;46H\033[4mExit\033[0m" << std::endl;
            break;
    }
}

unsigned SettingsGeneralMenu::update(unsigned &string_num, std::stack <std::unique_ptr<Menu>> &menus) {
    bool is_exit = false;
    KeyboardControl cntrl(game_settings);

    while (!is_exit) {
        Keys key = cntrl.read_key(right);
        is_exit = true;

        switch (key) {
            case up:
                string_num > 0 ? string_num -= 1 : string_num = options_count;
                break;
            case down:
                string_num < options_count ? string_num += 1 : string_num = 0;
                break;
            case enter:
                if (string_num == exit) {
                    menus.pop();
                    menus.top().get()->draw(string_num);
                } else {
                    Menu *m = nullptr;
                    if (string_num == snake) { // snake settings
                        m = new SettingsSnakeMenu(filename);
                    } else if (string_num == map) { // map settings
                        m = new SettingsMapMenu(filename);
                    } else if (string_num == graphic) { // graphic settings
                        m = new SettingsGraphicMenu(filename);
                    } else if (string_num == control) { // graphic settings
                        m = new SettingsControlMenu(filename);
                    }
                    string_num = 0;
                    menus.push(std::unique_ptr<Menu>(m));
                    menus.top().get()->draw(string_num);
                }
                break;
            default:
                is_exit = false;
                usleep(kSleepTime);
        }
    }
    return 0;
}

//************//


SettingsSnakeMenu::SettingsSnakeMenu(std::string file) : Menu(file), options_count(exit) {}

void SettingsSnakeMenu::pure_draw() {
    std::cout << "\033[17;46HSpeed:" << std::endl;
    std::cout << "\033[18;46HReset length at new level:" << std::endl;
    std::cout << "\033[19;46HExit" << std::endl;
}

void SettingsSnakeMenu::draw(unsigned string_num) {
    ConsoleUI::off_cursor();
    ConsoleUI console;
    console.clear_full_display();
    console.set_cursor(3, 1);

    print_logo();
    pure_draw();

    switch (string_num) {
        case speed:
            std::cout << "\033[17;46H\033[4mSpeed:\033[0m" << std::endl;
            break;
        case reset_length:
            std::cout << "\033[18;46H\033[4mReset length at new level:\033[0m" << std::endl;
            break;
        case exit:
            std::cout << "\033[19;46H\033[4mExit\033[0m" << std::endl;
            break;
    }
}

unsigned SettingsSnakeMenu::update(unsigned &string_num, std::stack <std::unique_ptr<Menu>> &menus) {
    bool is_exit = false;
    KeyboardControl control(game_settings);

    while (!is_exit) {
        Keys key = control.read_key(right);
        is_exit = true;

        switch (key) {
            case up:
                string_num > 0 ? string_num -= 1 : string_num = options_count;
                break;
            case down:
                string_num < options_count ? string_num += 1 : string_num = 0;
                break;
            case enter:
                if (string_num == speed) {
                    // TODO
                } else if (string_num == reset_length) {
                    // TODO
                } else if (string_num == exit) {
                    string_num = 0;
                    menus.pop();
                    menus.top().get()->draw(string_num);
                }
                break;
            default:
                is_exit = false;
                usleep(kSleepTime);
        }
    }

    return 0;
}

//************//


SettingsMapMenu::SettingsMapMenu(std::string file) : Menu(file), options_count(exit) {}

void SettingsMapMenu::pure_draw() {
    std::cout << "\033[17;46HMap length: " << std::endl;
    std::cout << "\033[18;46HMap width: " << std::endl;
    std::cout << "\033[19;46HEnable solid walls: " << std::endl;
    std::cout << "\033[20;46HEnable bonus apples: " << std::endl;
    std::cout << "\033[21;46HEnable teleports: " << std::endl;
    std::cout << "\033[22;46HShow score: " << std::endl;
    std::cout << "\033[23;46HExit" << std::endl;
}

void SettingsMapMenu::draw(unsigned string_num) {
    ConsoleUI::off_cursor();
    ConsoleUI console;
    console.clear_full_display();
    console.set_cursor(3, 1);

    print_logo();
    pure_draw();

    switch (string_num) {
        case length:
            std::cout << "\033[17;46H\033[4mMap length: \033[0m" << std::endl;
            break;
        case width:
            std::cout << "\033[18;46H\033[4mMap width: \033[0m" << std::endl;
            break;
        case solid_walls:
            std::cout << "\033[19;46H\033[4mEnable solid walls: \033[0m" << std::endl;
            break;
        case bonus_apples:
            std::cout << "\033[20;46H\033[4mEnable bonus apples: \033[0m" << std::endl;
            break;
        case teleports:
            std::cout << "\033[21;46H\033[4mEnable teleports: \033[0m" << std::endl;
            break;
        case show_score:
            std::cout << "\033[22;46H\033[4mShow score: \033[0m" << std::endl;
            break;
        case exit:
            std::cout << "\033[23;46H\033[4mExit\033[0m" << std::endl;
            break;
    }
}

unsigned SettingsMapMenu::update(unsigned &string_num, std::stack <std::unique_ptr<Menu>> &menus) {
    bool is_exit = false;
    KeyboardControl control(game_settings);

    while (!is_exit) {
        Keys key = control.read_key(right);
        is_exit = true;

        switch (key) {
            case up:
                string_num > 0 ? string_num -= 1 : string_num = options_count;
                break;
            case down:
                string_num < options_count ? string_num += 1 : string_num = 0;
                break;
            case enter:
                if (string_num == length) {
                    // TODO
                } else if (string_num == width) {
                    // TODO
                } else if (string_num == solid_walls) {
                    // TODO
                } else if (string_num == bonus_apples) {
                    // TODO
                } else if (string_num == teleports) {
                    // TODO
                } else if (string_num == show_score) {
                    // TODO
                } else if (string_num == exit) {
                    string_num = 0;
                    menus.pop();
                    menus.top().get()->draw(string_num);
                }
                break;
            default:
                is_exit = false;
                usleep(kSleepTime);
        }
    }
    return 0;
}

//************//


SettingsControlMenu::SettingsControlMenu(std::string file) : Menu(file), options_count(exit) {}

void SettingsControlMenu::pure_draw() {
    std::cout << "\033[17;46HUp key: " << std::endl;
    std::cout << "\033[18;46HDown key: " << std::endl;
    std::cout << "\033[19;46HLeft key: " << std::endl;
    std::cout << "\033[20;46HRight key: " << std::endl;
    std::cout << "\033[21;46HPause key: " << std::endl;
    std::cout << "\033[22;46HEnter key: " << std::endl;
    std::cout << "\033[23;46HExit" << std::endl;
}

void SettingsControlMenu::draw(unsigned string_num) {
    ConsoleUI::off_cursor();
    ConsoleUI console;
    console.clear_full_display();
    console.set_cursor(3, 1);

    print_logo();
    pure_draw();

    switch (string_num) {
        case up:
            std::cout << "\033[17;46H\033[4mUp key: \033[0m" << std::endl;
            break;
        case down:
            std::cout << "\033[18;46H\033[4mDown key: \033[0m" << std::endl;
            break;
        case left:
            std::cout << "\033[19;46H\033[4mLeft key: \033[0m" << std::endl;
            break;
        case right:
            std::cout << "\033[20;46H\033[4mRight key: \033[0m" << std::endl;
            break;
        case pause:
            std::cout << "\033[21;46H\033[4mPause key: \033[0m" << std::endl;
            break;
        case enter:
            std::cout << "\033[22;46H\033[4mEnter key: \033[0m" << std::endl;
            break;
        case exit:
            std::cout << "\033[23;46H\033[4mExit\033[0m" << std::endl;
            break;
    }
}

unsigned SettingsControlMenu::update(unsigned &string_num, std::stack <std::unique_ptr<Menu>> &menus) {
    bool is_exit = false;
    KeyboardControl control(game_settings);

    while (!is_exit) {
        Keys key = control.read_key(Keys::right);
        is_exit = true;

        switch (key) {
            case Keys::up:
                string_num > 0 ? string_num -= 1 : string_num = options_count;
                break;
            case Keys::down:
                string_num < options_count ? string_num += 1 : string_num = 0;
                break;
            case enter:
                if (string_num == up) {
                    // TODO
                } else if (string_num == down) {
                    // TODO
                } else if (string_num == left) {
                    // TODO
                } else if (string_num == right) {
                    // TODO
                } else if (string_num == pause) {
                    // TODO
                } else if (string_num == enter) {
                    // TODO
                } else if (string_num == exit) {
                    string_num = 0;
                    menus.pop();
                    menus.top().get()->draw(string_num);
                }
                break;
            default:
                is_exit = false;
                usleep(kSleepTime);
        }
    }
    return 0;
}

//************//


SettingsGraphicMenu::SettingsGraphicMenu(std::string file) : Menu(file), options_count(exit) {}

void SettingsGraphicMenu::pure_draw() {
    std::cout << "\033[17;46HSnake color: " << std::endl;
    std::cout << "\033[18;46HEmpty block color: " << std::endl;
    std::cout << "\033[19;46HWall color: " << std::endl;
    std::cout << "\033[20;46HTeleport color: " << std::endl;
    std::cout << "\033[21;46HBonus color: " << std::endl;
    std::cout << "\033[22;46HAntibonus color: " << std::endl;
    std::cout << "\033[23;46HSpeed bonus color: " << std::endl;
    std::cout << "\033[24;46HSpeed antibonus color: " << std::endl;
    std::cout << "\033[25;46HExit" << std::endl;
}

void SettingsGraphicMenu::draw(unsigned string_num) {
    ConsoleUI::off_cursor();
    ConsoleUI console;
    console.clear_full_display();
    console.set_cursor(3, 1);

    print_logo();
    pure_draw();

    switch (string_num) {
        case snake:
            std::cout << "\033[17;46H\033[4mSnake color: \033[0m" << std::endl;
            break;
        case empty_block:
            std::cout << "\033[18;46H\033[4mEmpty block color: \033[0m" << std::endl;
            break;
        case wall:
            std::cout << "\033[19;46H\033[4mWall color: \033[0m" << std::endl;
            break;
        case teleport:
            std::cout << "\033[20;46H\033[4mTeleport color: \033[0m" << std::endl;
            break;
        case bonus:
            std::cout << "\033[21;46H\033[4mBonus color: \033[0m" << std::endl;
            break;
        case anti_bonus:
            std::cout << "\033[22;46H\033[4mAntibonus color: \033[0m" << std::endl;
            break;
        case speed_bonus:
            std::cout << "\033[23;46H\033[4mSpeed bonus color: \033[0m" << std::endl;
            break;
        case anti_speed_bonus:
            std::cout << "\033[24;46H\033[4mSpeed antibonus color: \033[0m" << std::endl;
            break;
        case exit:
            std::cout << "\033[25;46H\033[4mExit\033[0m" << std::endl;
            break;
    }
}

unsigned SettingsGraphicMenu::update(unsigned &string_num, std::stack <std::unique_ptr<Menu>> &menus) {
    bool is_exit = false;
    KeyboardControl control(game_settings);

    while (!is_exit) {
        Keys key = control.read_key(right);
        is_exit = true;

        switch (key) {
            case up:
                string_num > 0 ? string_num -= 1 : string_num = options_count;
                break;
            case down:
                string_num < options_count ? string_num += 1 : string_num = 0;
                break;
            case enter:
                if (string_num == snake) {
                    // TODO
                } else if (string_num == empty_block) {
                    // TODO
                } else if (string_num == wall) {
                    // TODO
                } else if (string_num == teleport) {
                    // TODO
                } else if (string_num == bonus) {
                    // TODO
                } else if (string_num == anti_bonus) {
                    // TODO
                } else if (string_num == speed_bonus) {
                    // TODO
                } else if (string_num == anti_speed_bonus) {
                    // TODO
                } else if (string_num == exit) {
                    string_num = 0;
                    menus.pop();
                    menus.top().get()->draw(string_num);
                }
                break;
            default:
                is_exit = false;
                usleep(kSleepTime);
        }
    }
    return 0;
}

//************//


TitlesMenu::TitlesMenu(std::string file) : Menu(file) {}

void TitlesMenu::pure_draw() {}

void TitlesMenu::draw(unsigned string_num) {
    ConsoleUI console;
    console.clear_full_display();
    console.set_cursor(3, 1);

    print_logo();
}

unsigned TitlesMenu::update(unsigned &string_num, std::stack <std::unique_ptr<Menu>> &menus) {
    bool is_exit = false;
    KeyboardControl control(game_settings);

    while (!is_exit) {
        Keys key = control.read_key(right);
        is_exit = true;

        switch (key) {
            case enter:
                string_num = 0;
                menus.pop();
                menus.top().get()->draw(string_num);
                break;
            default:
                is_exit = false;
                usleep(kSleepTime);
        }
    }
    return 0;
}

//************//


GameInformationMenu::GameInformationMenu(std::string file) : Menu(file) {}

void GameInformationMenu::pure_draw() {
    std::cout << "\033[17;46HSnake color: ";
    std::cout << "\033[48;2;" + std::to_string(game_settings.snake_color.r) + ';' +
                 std::to_string(game_settings.snake_color.g) + ';' + std::to_string(game_settings.snake_color.b) + 'm'
              << "  " << std::endl;

    std::cout << "\033[0m" << "\033[18;46HEmpty block color: ";
    std::cout << "\033[48;2;" + std::to_string(game_settings.empty_color.r) + ';' +
                 std::to_string(game_settings.empty_color.g) + ';' + std::to_string(game_settings.empty_color.b) + 'm'
              << "  " << std::endl;

    std::cout << "\033[0m" << "\033[19;46HWall color: ";
    std::cout << "\033[48;2;" + std::to_string(game_settings.wall_color.r) + ';' +
                 std::to_string(game_settings.wall_color.g) + ';' + std::to_string(game_settings.wall_color.b) + 'm' <<
              "  " << std::endl;

    std::cout << "\033[0m" << "\033[20;46HTeleport color: ";
    std::cout << "\033[48;2;" + std::to_string(game_settings.teleport_color.r) + ';' +
                 std::to_string(game_settings.teleport_color.g) + ';' + std::to_string(game_settings.teleport_color.b) +
                 'm' << "  " << std::endl;

    std::cout << "\033[0m" << "\033[21;46HBonus color: ";
    std::cout << "\033[48;2;" + std::to_string(game_settings.bonus_color.r) + ';' +
                 std::to_string(game_settings.bonus_color.g) + ';' + std::to_string(game_settings.bonus_color.b) + 'm'
              << "  " << std::endl;

    std::cout << "\033[0m" << "\033[22;46HAntibonus color: ";
    std::cout << "\033[48;2;" + std::to_string(game_settings.antibonus_color.r) + ';' +
                 std::to_string(game_settings.antibonus_color.g) + ';' +
                 std::to_string(game_settings.antibonus_color.b) + 'm' << "  " << std::endl;

    std::cout << "\033[0m" << "\033[23;46HSpeed bonus color: ";
    std::cout << "\033[48;2;" + std::to_string(game_settings.speed_bonus_color.r) + ';' +
                 std::to_string(game_settings.speed_bonus_color.g) + ';' +
                 std::to_string(game_settings.speed_bonus_color.b) + 'm' << "  " << std::endl;

    std::cout << "\033[0m" << "\033[24;46HSpeed antibonus color: ";
    std::cout << "\033[48;2;" + std::to_string(game_settings.speed_antibonus_color.r) +
                 ';' + std::to_string(game_settings.speed_antibonus_color.g) + ';' +
                 std::to_string(game_settings.speed_antibonus_color.b) + 'm' << "  " << std::endl;

    std::cout << "\033[0m" << "\033[26;46HPress enter fot exit" << std::endl;
}

void GameInformationMenu::draw(unsigned string_num) {
    ConsoleUI console;
    console.clear_full_display();
    console.set_cursor(3, 1);

    print_logo();
    pure_draw();
}

unsigned GameInformationMenu::update(unsigned &string_num, std::stack <std::unique_ptr<Menu>> &menus) {
    bool is_exit = false;
    KeyboardControl control(game_settings);

    while (!is_exit) {
        Keys key = control.read_key(right);
        is_exit = true;

        switch (key) {
            case enter:
                string_num = 0;
                menus.pop();
                menus.top().get()->draw(string_num);
                break;
            default:
                is_exit = false;
                usleep(kSleepTime);
        }
    }
    return 0;
}