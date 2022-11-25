#include "menu.h"

Menu::Menu(std::string file) : filename(file) {
    ConsoleUI::off_cursor();
    parser(game_settings, filename);
}

void Menu::print_cell_info(unsigned y) {
    ConsoleUI console;

    console.set_cursor(y++, 46);
    std::cout << "Snake color: ";
    console.print_rgb(game_settings.snake_color.r,
                      game_settings.snake_color.g,
                      game_settings.snake_color.b);
    console.reset();

    console.set_cursor(y++, 46);
    std::cout << "Empty block color: ";
    console.print_rgb(game_settings.empty_color.r,
                      game_settings.empty_color.g,
                      game_settings.empty_color.b);
    console.reset();

    console.set_cursor(y++, 46);
    std::cout << "Wall color: ";
    console.print_rgb(game_settings.wall_color.r,
                      game_settings.wall_color.g,
                      game_settings.wall_color.b);
    console.reset();

    console.set_cursor(y++, 46);
    std::cout << "Teleport color: ";
    console.print_rgb(game_settings.teleport_color.r,
                      game_settings.teleport_color.g,
                      game_settings.teleport_color.b);
    console.reset();

    console.set_cursor(y++, 46);
    std::cout << "Bonus color: ";
    console.print_rgb(game_settings.bonus_color.r,
                      game_settings.bonus_color.g,
                      game_settings.bonus_color.b);
    console.reset();

    console.set_cursor(y++, 46);
    std::cout << "Antibonus color: ";
    console.print_rgb(game_settings.antibonus_color.r,
                      game_settings.antibonus_color.g,
                      game_settings.antibonus_color.b);
    console.reset();

    console.set_cursor(y++, 46);
    std::cout << "Speed bonus color: ";
    console.print_rgb(game_settings.speed_bonus_color.r,
                      game_settings.speed_bonus_color.g,
                      game_settings.speed_bonus_color.b);
    console.reset();

    console.set_cursor(y++, 46);
    std::cout << "Speed antibonus color: ";
    console.print_rgb(game_settings.speed_antibonus_color.r,
                      game_settings.speed_antibonus_color.g,
                      game_settings.speed_antibonus_color.b);
    console.reset();

    console.set_cursor(y+1, 46);
    std::cout << "Exit" << std::endl;
}

MainMenu::MainMenu(std::string file, bool random_apples) : Menu(file), options_count(exit),
                                                           random_apples(random_apples) {}

void MainMenu::pure_draw() {
    ConsoleUI console;
    console.set_cursor(17, 33);
    std::cout << "Start game" << std::endl;
    console.set_cursor(18, 33);
    std::cout << "Leaderboard" << std::endl;
    console.set_cursor(19, 33);
    std::cout << "Settings" << std::endl;
    console.set_cursor(20, 33);
    std::cout << "Cell information" << std::endl;
    console.set_cursor(21, 33);
    std::cout << "Credits" << std::endl;
    console.set_cursor(22, 33);
    std::cout << "Exit" << std::endl;
}

void MainMenu::draw(unsigned string_num) {
    parser(game_settings, filename);
    ConsoleUI::off_cursor();
    ConsoleUI console;
    console.clear_full_display();
    console.set_cursor(3, 1);

    print_logo();
    pure_draw();

    switch (string_num) {
        case start:
            console.set_cursor(17, 33);
            console.underline();
            std::cout << "Start game" << std::endl;
            console.reset();
            break;
        case leaderboard:
            console.set_cursor(18, 33);
            console.underline();
            std::cout << "Leaderboard" << std::endl;
            console.reset();
            break;
        case settings:
            console.set_cursor(19, 33);
            console.underline();
            std::cout << "Settings" << std::endl;
            console.reset();
            break;
        case information:
            console.set_cursor(20, 33);
            console.underline();
            std::cout << "Cell information" << std::endl;
            console.reset();
            break;
        case credits:
            console.set_cursor(21, 33);
            console.underline();
            std::cout << "Credits" << std::endl;
            console.reset();
            break;
        case exit:
            console.set_cursor(22, 33);
            console.underline();
            std::cout << "Exit" << std::endl;
            console.reset();
            break;
    }
}

unsigned MainMenu::update(unsigned &string_num, std::stack <std::unique_ptr<Menu>> &menus) {
    bool is_exit = false;
    KeyboardControl control(game_settings);

    while (!is_exit) {
        // initializes with right direction argument bcs there is no interruption option in menu
        Keys key = control.read_key(Keys::interruption);
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
    ConsoleUI console;
    console.set_cursor(16, 36);
    std::cout << "Resume" << std::endl;
    console.set_cursor(17, 36);
    std::cout << "Restart" << std::endl;
    console.set_cursor(18, 36);
    std::cout << "Cell information" << std::endl;
    console.set_cursor(20, 36);
    std::cout << "Exit" << std::endl;
}

void PauseMenu::draw(unsigned string_num) {
    parser(game_settings, filename);
    ConsoleUI::off_cursor();
    ConsoleUI console;
    console.clear_full_display();
    console.set_cursor(3, 1);

    print_logo();
    pure_draw();

    switch (string_num) {
        case resume:
            console.set_cursor(16, 36);
            console.underline();
            std::cout << "Resume" << std::endl;
            console.reset();
            break;
        case restart:
            console.set_cursor(17, 36);
            console.underline();
            std::cout << "Restart" << std::endl;
            console.reset();
            break;
        case information:
            console.set_cursor(18, 36);
            console.underline();
            std::cout << "Cell information" << std::endl;
            console.reset();
            break;
        case exit:
            console.set_cursor(20, 36);
            console.underline();
            std::cout << "Exit" << std::endl;
            console.reset();
            break;
    }
}

unsigned PauseMenu::update(unsigned &string_num, std::stack <std::unique_ptr<Menu>> &menus) {
    bool is_exit = false;
    KeyboardControl control(game_settings);

    while (!is_exit) {
        Keys key = control.read_key(Keys::interruption);
        is_exit = true;
        switch (key) {
            case up:
                string_num > 0 ? string_num -= 1 : string_num = options_count;
                break;
            case down:
                string_num < options_count ? string_num += 1 : string_num = 0;
                break;
            case enter:
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
    ConsoleUI console;
    if (!file.good()) {
        console.set_cursor(17, 46);
        std::cout << "History is empty" << std::endl;
        console.set_cursor(18, 46);
        std::cout << "Press enter for exit" << std::endl;
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
        console.set_cursor(string_num++, 32);
        std::cout << data << "\t|\t" << score << std::endl;
    }
    file.close();
    console.set_cursor(string_num + 1, 32);
    std::cout << "Press enter for exit" << std::endl;
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
        Keys key = control.read_key(Keys::interruption);
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
    ConsoleUI::set_cursor(17, 46);
    std::cout << "Snake settings" << std::endl;
    ConsoleUI::set_cursor(18, 46);
    std::cout << "Map settings" << std::endl;
    ConsoleUI::set_cursor(19, 46);
    std::cout << "Graphic settings" << std::endl;
    ConsoleUI::set_cursor(20, 46);
    std::cout << "Control settings" << std::endl;
    ConsoleUI::set_cursor(22, 46);
    std::cout << "Read and save settings" << std::endl;
    ConsoleUI::set_cursor(24, 46);
    std::cout << "Exit" << std::endl;
}

void SettingsGeneralMenu::draw(unsigned string_num) {
    parser(game_settings, filename);
    ConsoleUI::off_cursor();
    ConsoleUI console;
    console.clear_full_display();
    console.set_cursor(3, 1);

    print_logo();
    pure_draw();

    switch (string_num) {
        case snake:
            console.set_cursor(17, 46);
            console.underline();
            std::cout << "Snake settings" << std::endl;
            console.reset();
            break;
        case map:
            console.set_cursor(18, 46);
            console.underline();
            std::cout << "Map settings" << std::endl;
            console.reset();
            break;
        case graphic:
            console.set_cursor(19, 46);
            console.underline();
            std::cout << "Graphic settings" << std::endl;
            console.reset();
            break;
        case control:
            console.set_cursor(20, 46);
            console.underline();
            std::cout << "Control settings" << std::endl;
            console.reset();
            break;
        case save_sets:
            console.set_cursor(22, 46);
            console.underline();
            std::cout << "Read and save settings" << std::endl;
            console.reset();
            break;
        case exit:
            console.set_cursor(24, 46);
            console.underline();
            std::cout << "Exit" << std::endl;
            console.reset();
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
                    string_num = 0;
                    menus.pop();
                } else {
                    Menu *m = nullptr;
                    if (string_num == snake) {
                        m = new SettingsSnakeMenu(filename);
                    } else if (string_num == map) {
                        m = new SettingsMapMenu(filename);
                    } else if (string_num == graphic) {
                        m = new SettingsGraphicMenu(filename);
                    } else if (string_num == control) {
                        m = new SettingsControlMenu(filename);
                    } else {
                        m = new SavedSettingsMenu(filename);
                    }
                    string_num = 0;
                    menus.push(std::unique_ptr<Menu>(m));
                }
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


SettingsSnakeMenu::SettingsSnakeMenu(std::string file) : Menu(file), options_count(exit) {}

void SettingsSnakeMenu::pure_draw() {
    ConsoleUI console;
    console.set_cursor(17, 46);
    std::cout << "Speed: " << game_settings.speed << std::endl;
    console.set_cursor(18, 46);
    std::cout << "Reset length at new level: " << game_settings.reset_length << std::endl;
    console.set_cursor(20, 46);
    std::cout << "Exit" << std::endl;
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
            console.set_cursor(17, 46);
            console.underline();
            std::cout << "Speed: " << game_settings.speed << std::endl;
            console.reset();
            break;
        case reset_length:
            console.set_cursor(18, 46);
            console.underline();
            std::cout << "Reset length at new level: " << game_settings.reset_length << std::endl;
            console.reset();
            break;
        case exit:
            console.set_cursor(20, 46);
            console.underline();
            std::cout << "Exit" << std::endl;
            console.reset();
            break;
    }
}

unsigned SettingsSnakeMenu::update(unsigned &string_num, std::stack <std::unique_ptr<Menu>> &menus) {
    bool is_exit = false;
    KeyboardControl control(game_settings);

    while (!is_exit) {
        Keys key = control.read_key(Keys::interruption);
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
                    ConsoleUI::set_cursor(17, 53);
                    ConsoleUI::highlight(3);
                    ConsoleUI::set_cursor(17, 53);
                    ConsoleUI::highlight(0);
                    game_settings.speed = control.read_float_option();
                    replace_float_setting(filename, "speed", game_settings.speed);
                    ConsoleUI::reset();
                } else if (string_num == reset_length) {
                    ConsoleUI::set_cursor(18, 73);
                    ConsoleUI::highlight(1);
                    ConsoleUI::set_cursor(18, 73);
                    ConsoleUI::highlight(0);
                    game_settings.reset_length = control.read_option();
                    replace_setting(filename, "reset_length", game_settings.reset_length);
                    ConsoleUI::reset();
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
    ConsoleUI console;
    console.set_cursor(17, 46);
    std::cout << "Map length: " << game_settings.map_length << std::endl;
    console.set_cursor(18, 46);
    std::cout << "Map width: " << game_settings.map_width << std::endl;
    console.set_cursor(19, 46);
    std::cout << "Enable solid walls: " << game_settings.solid_wall << std::endl;
    console.set_cursor(20, 46);
    std::cout << "Enable bonus apples: " << game_settings.bonus_apples << std::endl;
    console.set_cursor(21, 46);
    std::cout << "Show score: " << game_settings.score << std::endl;
    console.set_cursor(23, 46);
    std::cout << "Make custom map" << std::endl;
    console.set_cursor(25, 46);
    std::cout << "Exit" << std::endl;
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
            console.set_cursor(17, 46);
            console.underline();
            std::cout << "Map length: " << game_settings.map_length << std::endl;
            console.reset();
            break;
        case width:
            console.set_cursor(18, 46);
            console.underline();
            std::cout << "Map width: " << game_settings.map_width << std::endl;
            console.reset();
            break;
        case solid_walls:
            console.set_cursor(19, 46);
            console.underline();
            std::cout << "Enable solid walls: " << game_settings.solid_wall << std::endl;
            console.reset();
            break;
        case bonus_apples:
            console.set_cursor(20, 46);
            console.underline();
            std::cout << "Enable bonus apples: " << game_settings.bonus_apples << std::endl;
            console.reset();
            break;
        case show_score:
            console.set_cursor(21, 46);
            console.underline();
            std::cout << "Show score: " << game_settings.score << std::endl;
            console.reset();
            break;
        case custom_map:
            console.set_cursor(23, 46);
            console.underline();
            std::cout << "Make custom map" << std::endl;
            console.reset();
            break;
        case exit:
            console.set_cursor(25, 46);
            console.underline();
            std::cout << "Exit" << std::endl;
            console.reset();
            break;
    }
}

unsigned SettingsMapMenu::update(unsigned &string_num, std::stack <std::unique_ptr<Menu>> &menus) {
    bool is_exit = false;
    KeyboardControl control(game_settings);

    while (!is_exit) {
        Keys key = control.read_key(Keys::interruption);
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
                    ConsoleUI::set_cursor(17, 58);
                    ConsoleUI::highlight(2);
                    ConsoleUI::set_cursor(17, 58);
                    ConsoleUI::highlight(0);
                    game_settings.map_length = control.read_option();
                    replace_setting(filename, "map_length", game_settings.map_length);
                    ConsoleUI::reset();

                    MapModel map(game_settings); // for update map.txt
                    write_map_to_file(map);
                } else if (string_num == width) {
                    ConsoleUI::set_cursor(18, 57);
                    ConsoleUI::highlight(2);
                    ConsoleUI::set_cursor(18, 57);
                    ConsoleUI::highlight(0);
                    game_settings.map_width = control.read_option();
                    replace_setting(filename, "map_width", game_settings.map_width);
                    ConsoleUI::reset();

                    MapModel map(game_settings); // for update map.txt
                    write_map_to_file(map);
                } else if (string_num == solid_walls) {
                    ConsoleUI::set_cursor(19, 66);
                    ConsoleUI::highlight(1);
                    ConsoleUI::set_cursor(19, 66);
                    ConsoleUI::highlight(0);
                    game_settings.solid_wall = control.read_option();
                    replace_setting(filename, "solid_wall", game_settings.solid_wall);
                    ConsoleUI::reset();
                } else if (string_num == bonus_apples) {
                    ConsoleUI::set_cursor(20, 67);
                    ConsoleUI::highlight(1);
                    ConsoleUI::set_cursor(20, 67);
                    ConsoleUI::highlight(0);
                    game_settings.bonus_apples = control.read_option();
                    replace_setting(filename, "bonus_apples", game_settings.bonus_apples);
                    ConsoleUI::reset();
                } else if (string_num == show_score) {
                    ConsoleUI::set_cursor(21, 58);
                    ConsoleUI::highlight(1);
                    ConsoleUI::set_cursor(21, 58);
                    ConsoleUI::highlight(0);
                    game_settings.score = control.read_option();
                    replace_setting(filename, "score", game_settings.score);
                    ConsoleUI::reset();
                } else if (string_num == custom_map) {
                    string_num = 0;
                    Menu *m = new CustomMapSettingsMenu(filename);
                    menus.push(std::unique_ptr<Menu>(m));
                    menus.top().get()->draw(string_num);
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

void SettingsControlMenu::print_key(char key) {
    switch (key) {
        case 72:
            std::cout << "↑" << std::endl;
            break;
        case 75:
            std::cout << "←" << std::endl;
            break;
        case 80:
            std::cout << "↓" << std::endl;
            break;
        case 77:
            std::cout << "→" << std::endl;
            break;
        case 27:
            std::cout << "Escape" << std::endl;
            break;
        case 10:
            std::cout << "Enter" << std::endl;
            break;
        default:
            std::cout << key << std::endl;
            break;
    }
}

void SettingsControlMenu::pure_draw() {
    ConsoleUI console;
    console.set_cursor(17, 46);
    std::cout << "Up key: ";
    SettingsControlMenu::print_key(game_settings.key_up);

    console.set_cursor(18, 46);
    std::cout << "Down key: ";
    SettingsControlMenu::print_key(game_settings.key_down);

    console.set_cursor(19, 46);
    std::cout << "Left key: ";
    SettingsControlMenu::print_key(game_settings.key_left);

    console.set_cursor(20, 46);
    std::cout << "Right key: ";
    SettingsControlMenu::print_key(game_settings.key_right);

    console.set_cursor(21, 46);
    std::cout << "Pause key: ";
    SettingsControlMenu::print_key(game_settings.key_pause);

    console.set_cursor(22, 46);
    std::cout << "Enter key: ";
    SettingsControlMenu::print_key(game_settings.key_enter);

    console.set_cursor(23, 46);
    std::cout << "Teleport key: ";
    SettingsControlMenu::print_key(game_settings.key_teleport);

    console.set_cursor(24, 46);
    std::cout << "Wall key: ";
    SettingsControlMenu::print_key(game_settings.key_wall);

    console.set_cursor(25, 46);
    std::cout << "Empty key: ";
    SettingsControlMenu::print_key(game_settings.key_empty);

    console.set_cursor(27, 46);
    std::cout << "Exit" << std::endl;
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
            console.set_cursor(17, 46);
            console.underline();
            std::cout << "Up key: ";
            SettingsControlMenu::print_key(game_settings.key_up);
            console.reset();
            break;
        case down:
            console.set_cursor(18, 46);
            console.underline();
            std::cout << "Down key: ";
            SettingsControlMenu::print_key(game_settings.key_down);
            console.reset();
            break;
        case left:
            console.set_cursor(19, 46);
            console.underline();
            std::cout << "Left key: ";
            SettingsControlMenu::print_key(game_settings.key_left);
            console.reset();
            break;
        case right:
            console.set_cursor(20, 46);
            console.underline();
            std::cout << "Right key: ";
            SettingsControlMenu::print_key(game_settings.key_right);
            console.reset();
            break;
        case pause:
            console.set_cursor(21, 46);
            console.underline();
            std::cout << "Pause key: ";
            SettingsControlMenu::print_key(game_settings.key_pause);
            console.reset();
            break;
        case enter:
            console.set_cursor(22, 46);
            console.underline();
            std::cout << "Enter key: ";
            SettingsControlMenu::print_key(game_settings.key_enter);
            console.reset();
            break;
        case teleport:
            console.set_cursor(23, 46);
            console.underline();
            std::cout << "Teleport key: ";
            SettingsControlMenu::print_key(game_settings.key_teleport);
            console.reset();
            break;
        case wall:
            console.set_cursor(24, 46);
            console.underline();
            std::cout << "Wall key: ";
            SettingsControlMenu::print_key(game_settings.key_wall);
            console.reset();
            break;
        case empty:
            console.set_cursor(25, 46);
            console.underline();
            std::cout << "Wall key: ";
            SettingsControlMenu::print_key(game_settings.key_empty);
            console.reset();
            break;
        case exit:
            console.set_cursor(27, 46);
            console.underline();
            std::cout << "Exit" << std::endl;
            console.reset();
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
                    ConsoleUI::set_cursor(17, 54);
                    ConsoleUI::highlight(1);
                    ConsoleUI::set_cursor(17, 54);
                    ConsoleUI::highlight(0);
                    game_settings.key_up = control.read_char_option();
                    replace_char_setting(filename, "key_up", game_settings.key_up);
                    ConsoleUI::reset();
                } else if (string_num == down) {
                    ConsoleUI::set_cursor(18, 56);
                    ConsoleUI::highlight(1);
                    ConsoleUI::set_cursor(18, 56);
                    ConsoleUI::highlight(0);
                    game_settings.key_down = control.read_char_option();
                    replace_char_setting(filename, "key_down", game_settings.key_down);
                    ConsoleUI::reset();
                } else if (string_num == left) {
                    ConsoleUI::set_cursor(19, 56);
                    ConsoleUI::highlight(1);
                    ConsoleUI::set_cursor(19, 56);
                    ConsoleUI::highlight(0);
                    game_settings.key_left = control.read_char_option();
                    replace_char_setting(filename, "key_left", game_settings.key_left);
                    ConsoleUI::reset();
                } else if (string_num == right) {
                    ConsoleUI::set_cursor(20, 57);
                    ConsoleUI::highlight(1);
                    ConsoleUI::set_cursor(20, 57);
                    ConsoleUI::highlight(0);
                    game_settings.key_right = control.read_char_option();
                    replace_char_setting(filename, "key_right", game_settings.key_right);
                    ConsoleUI::reset();
                } else if (string_num == pause) {
                    ConsoleUI::set_cursor(21, 57);
                    ConsoleUI::highlight(6);
                    ConsoleUI::set_cursor(21, 57);
                    ConsoleUI::highlight(0);
                    game_settings.key_pause = control.read_char_option();
                    replace_char_setting(filename, "key_pause", game_settings.key_pause);
                    ConsoleUI::reset();
                } else if (string_num == enter) {
                    ConsoleUI::set_cursor(22, 57);
                    ConsoleUI::highlight(5);
                    ConsoleUI::set_cursor(22, 57);
                    ConsoleUI::highlight(0);
                    game_settings.key_enter = control.read_char_option();
                    replace_char_setting(filename, "key_enter", game_settings.key_enter);
                    ConsoleUI::reset();
                } else if (string_num == teleport) {
                    ConsoleUI::set_cursor(23, 57);
                    ConsoleUI::highlight(5);
                    ConsoleUI::set_cursor(23, 57);
                    ConsoleUI::highlight(0);
                    game_settings.key_teleport = control.read_char_option();
                    replace_char_setting(filename, "key_teleport", game_settings.key_teleport);
                    ConsoleUI::reset();
                } else if (string_num == wall) {
                    ConsoleUI::set_cursor(24, 57);
                    ConsoleUI::highlight(5);
                    ConsoleUI::set_cursor(24, 57);
                    ConsoleUI::highlight(0);
                    game_settings.key_wall = control.read_char_option();
                    replace_char_setting(filename, "key_wall", game_settings.key_wall);
                    ConsoleUI::reset();
                } else if (string_num == empty) {
                    ConsoleUI::set_cursor(25, 57);
                    ConsoleUI::highlight(5);
                    ConsoleUI::set_cursor(25, 57);
                    ConsoleUI::highlight(0);
                    game_settings.key_empty = control.read_char_option();
                    replace_char_setting(filename, "key_empty", game_settings.key_empty);
                    ConsoleUI::reset();
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
    ConsoleUI console;

    console.set_cursor(17, 46);
    std::cout << "Graphic mode: " << game_settings.view_mode;
    console.reset();

    console.set_cursor(19, 46);
    std::cout << "Mode 2 colors: ";

    print_cell_info(20);
}

void SettingsGraphicMenu::draw(unsigned string_num) {
    ConsoleUI::off_cursor();
    ConsoleUI console;
    console.clear_full_display();
    console.set_cursor(3, 1);

    print_logo();
    pure_draw();

    switch (string_num) {
        case mode:
            console.set_cursor(17, 46);
            console.underline();
            std::cout << "Graphic mode: " << game_settings.view_mode;
            console.reset();
            break;
        case snake:
            console.set_cursor(20, 46);
            console.underline();
            std::cout << "Snake color: ";
            console.print_rgb(game_settings.snake_color.r,
                              game_settings.snake_color.g,
                              game_settings.snake_color.b);
            console.reset();
            break;
        case empty_block:
            console.set_cursor(21, 46);
            console.underline();
            std::cout << "Empty block color: ";
            console.print_rgb(game_settings.empty_color.r,
                              game_settings.empty_color.g,
                              game_settings.empty_color.b);
            console.reset();
            break;
        case wall:
            console.set_cursor(22, 46);
            console.underline();
            std::cout << "Wall color: ";
            console.print_rgb(game_settings.wall_color.r,
                              game_settings.wall_color.g,
                              game_settings.wall_color.b);
            console.reset();
            break;
        case teleport:
            console.set_cursor(23, 46);
            console.underline();
            std::cout << "Teleport color: ";
            console.print_rgb(game_settings.teleport_color.r,
                              game_settings.teleport_color.g,
                              game_settings.teleport_color.b);
            console.reset();
            break;
        case bonus:
            console.set_cursor(24, 46);
            console.underline();
            std::cout << "Bonus color: ";
            console.print_rgb(game_settings.bonus_color.r,
                              game_settings.bonus_color.g,
                              game_settings.bonus_color.b);
            console.reset();
            break;
        case anti_bonus:
            console.set_cursor(25, 46);
            console.underline();
            std::cout << "Antibonus color: ";
            console.print_rgb(game_settings.antibonus_color.r,
                              game_settings.antibonus_color.g,
                              game_settings.antibonus_color.b);
            console.reset();
            break;
        case speed_bonus:
            console.set_cursor(26, 46);
            console.underline();
            std::cout << "Speed bonus color: ";
            console.print_rgb(game_settings.speed_bonus_color.r,
                              game_settings.speed_bonus_color.g,
                              game_settings.speed_bonus_color.b);
            console.reset();
            break;
        case anti_speed_bonus:
            console.set_cursor(27, 46);
            console.underline();
            std::cout << "Speed antibonus color: ";
            console.print_rgb(game_settings.speed_antibonus_color.r,
                              game_settings.speed_antibonus_color.g,
                              game_settings.speed_antibonus_color.b);
            console.reset();
            break;
        case exit:
            console.set_cursor(29, 46);
            console.underline();
            std::cout << "Exit" << std::endl;
            console.reset();
            break;
    }
}

unsigned SettingsGraphicMenu::update(unsigned &string_num, std::stack <std::unique_ptr<Menu>> &menus) {
    bool is_exit = false;
    KeyboardControl control(game_settings);

    while (!is_exit) {
        Keys key = control.read_key(Keys::interruption);
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
                    ConsoleUI::set_cursor(20, 59);
                    ConsoleUI::highlight(2);
                    ConsoleUI::set_cursor(20, 59);
                    ConsoleUI::highlight(0);
                    game_settings.snake_color = control.read_rgb_option();
                    replace_rgb_setting(filename, "snake_color", game_settings.snake_color);
                    ConsoleUI::reset();
                } else if (string_num == empty_block) {
                    ConsoleUI::set_cursor(21, 65);
                    ConsoleUI::highlight(2);
                    ConsoleUI::set_cursor(21, 65);
                    ConsoleUI::highlight(0);
                    game_settings.empty_color = control.read_rgb_option();
                    replace_rgb_setting(filename, "empty_color", game_settings.empty_color);
                    ConsoleUI::reset();
                } else if (string_num == wall) {
                    ConsoleUI::set_cursor(22, 58);
                    ConsoleUI::highlight(2);
                    ConsoleUI::set_cursor(22, 58);
                    ConsoleUI::highlight(0);
                    game_settings.wall_color = control.read_rgb_option();
                    replace_rgb_setting(filename, "wall_color", game_settings.wall_color);
                    ConsoleUI::reset();
                } else if (string_num == teleport) {
                    ConsoleUI::set_cursor(23, 62);
                    ConsoleUI::highlight(2);
                    ConsoleUI::set_cursor(23, 62);
                    ConsoleUI::highlight(0);
                    game_settings.teleport_color = control.read_rgb_option();
                    replace_rgb_setting(filename, "teleport_color", game_settings.teleport_color);
                    ConsoleUI::reset();
                } else if (string_num == bonus) {
                    ConsoleUI::set_cursor(24, 59);
                    ConsoleUI::highlight(2);
                    ConsoleUI::set_cursor(24, 59);
                    ConsoleUI::highlight(0);
                    game_settings.bonus_color = control.read_rgb_option();
                    replace_rgb_setting(filename, "bonus_color", game_settings.bonus_color);
                    ConsoleUI::reset();
                } else if (string_num == anti_bonus) {
                    ConsoleUI::set_cursor(25, 63);
                    ConsoleUI::highlight(2);
                    ConsoleUI::set_cursor(25, 63);
                    ConsoleUI::highlight(0);
                    game_settings.antibonus_color = control.read_rgb_option();
                    replace_rgb_setting(filename, "antibonus_color", game_settings.antibonus_color);
                    ConsoleUI::reset();
                } else if (string_num == speed_bonus) {
                    ConsoleUI::set_cursor(26, 65);
                    ConsoleUI::highlight(2);
                    ConsoleUI::set_cursor(26, 65);
                    ConsoleUI::highlight(0);
                    game_settings.speed_bonus_color = control.read_rgb_option();
                    replace_rgb_setting(filename, "speed_bonus_color", game_settings.speed_bonus_color);
                    ConsoleUI::reset();
                } else if (string_num == anti_speed_bonus) {
                    ConsoleUI::set_cursor(27, 69);
                    ConsoleUI::highlight(2);
                    ConsoleUI::set_cursor(27, 69);
                    ConsoleUI::highlight(0);
                    game_settings.speed_antibonus_color = control.read_rgb_option();
                    replace_rgb_setting(filename, "speed_antibonus_color", game_settings.speed_antibonus_color);
                    ConsoleUI::reset();
                } else if (string_num == mode) {
                    ConsoleUI::set_cursor(17, 60);
                    ConsoleUI::highlight(1);
                    ConsoleUI::set_cursor(17, 60);
                    ConsoleUI::highlight(0);
                    unsigned new_mode = control.read_option();
                    if (new_mode > 2) {
                        new_mode = 2;
                    }
                    game_settings.view_mode = new_mode;
                    replace_setting(filename, "view_mode", game_settings.view_mode);
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


SavedSettingsMenu::SavedSettingsMenu(std::string file) : Menu(file), options_count(exit) {}

void SavedSettingsMenu::pure_draw() {
    ConsoleUI::set_cursor(17, 46);
    std::cout << "Save first settings" << std::endl;
    ConsoleUI::set_cursor(18, 46);
    std::cout << "Save second settings" << std::endl;
    ConsoleUI::set_cursor(19, 46);
    std::cout << "Save third settings" << std::endl;
    ConsoleUI::set_cursor(21, 46);
    std::cout << "Read first settings" << std::endl;
    ConsoleUI::set_cursor(22, 46);
    std::cout << "Read second settings" << std::endl;
    ConsoleUI::set_cursor(23, 46);
    std::cout << "Read third settings" << std::endl;
    ConsoleUI::set_cursor(25, 46);
    std::cout << "Exit" << std::endl;
}

void SavedSettingsMenu::draw(unsigned string_num) {
    parser(game_settings, filename);
    ConsoleUI::off_cursor();
    ConsoleUI console;
    console.clear_full_display();
    console.set_cursor(3, 1);

    print_logo();
    pure_draw();

    switch (string_num) {
        case save1:
            console.set_cursor(17, 46);
            console.underline();
            std::cout << "Save first settings" << std::endl;
            console.reset();
            break;
        case save2:
            console.set_cursor(18, 46);
            console.underline();
            std::cout << "Save second settings" << std::endl;
            console.reset();
            break;
        case save3:
            console.set_cursor(19, 46);
            console.underline();
            std::cout << "Save third settings" << std::endl;
            console.reset();
            break;
        case read1:
            console.set_cursor(21, 46);
            console.underline();
            std::cout << "Read first settings" << std::endl;
            console.reset();
            break;
        case read2:
            console.set_cursor(22, 46);
            console.underline();
            std::cout << "Read second settings" << std::endl;
            console.reset();
            break;
        case read3:
            console.set_cursor(23, 46);
            console.underline();
            std::cout << "Read third settings" << std::endl;
            console.reset();
            break;
        case exit:
            console.set_cursor(25, 46);
            console.underline();
            std::cout << "Exit" << std::endl;
            console.reset();
            break;
    }
}

unsigned SavedSettingsMenu::update(unsigned int &string_num, std::stack <std::unique_ptr<Menu>> &menus) {
    bool is_exit = false;
    KeyboardControl control(game_settings);

    while (!is_exit) {
        Keys key = control.read_key(Keys::interruption);
        is_exit = true;

        switch (key) {
            case up:
                string_num > 0 ? string_num -= 1 : string_num = options_count;
                break;
            case down:
                string_num < options_count ? string_num += 1 : string_num = 0;
                break;
            case enter:
                if (string_num == save1) {
                    copy_file("settings.txt", "presets/settings1.txt");
                    copy_file("map.txt", "presets/map1.txt");
                } else if (string_num == save2) {
                    copy_file("settings.txt", "presets/settings2.txt");
                    copy_file("map.txt", "presets/map2.txt");
                } else if (string_num == save3) {
                    copy_file("settings.txt", "presets/settings3.txt");
                    copy_file("map.txt", "presets/map3.txt");
                } else if (string_num == read1) {
                    copy_file("presets/settings1.txt", "settings.txt");
                    copy_file("presets/map1.txt", "map.txt");
                } else if (string_num == read2) {
                    copy_file("presets/settings2.txt", "settings.txt");
                    copy_file("presets/map2.txt", "map.txt");
                } else if (string_num == read3) {
                    copy_file("presets/settings3.txt", "settings.txt");
                    copy_file("presets/map3.txt", "map.txt");
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


CustomMapSettingsMenu::CustomMapSettingsMenu(std::string file) : Menu(file),
                                                                 map_model(read_map_from_file(game_settings)),
                                                                 map_view(map_model, game_settings), i(2), j(2) {}

void CustomMapSettingsMenu::pure_draw() {
    ConsoleUI console;
    ConsoleUI::set_cursor(1, 1);
    console.clear_full_display();
    map_view.print();

    ConsoleUI::set_cursor(game_settings.map_width + 2, 1);
    std::cout << "Press enter for quit" << std::endl;
}

void CustomMapSettingsMenu::draw(unsigned string_num) {
    pure_draw();
}

unsigned CustomMapSettingsMenu::update(unsigned &string_num, std::stack <std::unique_ptr<Menu>> &menus) {
    bool is_exit = false;
    KeyboardControl control(game_settings);
    ConsoleUI::set_cursor(i, j * 2 - 1);
    ConsoleUI::highlight(2);

    while (!is_exit) {
        Keys key = control.read_key(Keys::interruption);
        is_exit = true;

        switch (key) {
            case up:
                i = i > 2 ? i - 1 : game_settings.map_width - 1;
                pure_draw();
                ConsoleUI::set_cursor(i, j * 2 - 1);
                ConsoleUI::highlight(2);
                break;
            case down:
                i = i < game_settings.map_width - 1 ? i + 1 : 2;
                pure_draw();
                ConsoleUI::set_cursor(i, j * 2 - 1);
                ConsoleUI::highlight(2);
                break;
            case left:
                j = (j > 2) ? j - 1 : game_settings.map_length - 1;
                pure_draw();
                ConsoleUI::set_cursor(i, j * 2 - 1);
                ConsoleUI::highlight(2);
                break;
            case right:
                j = (j < game_settings.map_length - 1) ? j + 1 : 2;
                pure_draw();
                ConsoleUI::set_cursor(i, j * 2 - 1);
                ConsoleUI::highlight(2);
                break;
            case teleport:
                map_model.set_cell(game_settings.map_width - i, j - 1, teleport_c);
                map_model.set_cell(i - 1, game_settings.map_width - j, teleport_c);
                break;
            case wall:
                map_model.set_cell(game_settings.map_width - i, j - 1, wall_c);
                break;
            case empty:
                if (map_model.check_cell(game_settings.map_width - i, j - 1) == teleport_c) {
                    map_model.set_cell(i - 1, game_settings.map_width - j, empty_c);
                }
                map_model.set_cell(game_settings.map_width - i, j - 1, empty_c);
                break;
            case enter:
                string_num = 0;
                write_map_to_file(map_model);
                ConsoleUI::off_cursor();
                menus.pop();
                menus.top().get()->draw(string_num);
                break;
            default:
                continue;
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
        Keys key = control.read_key(Keys::interruption);
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
    print_cell_info(17);
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
        Keys key = control.read_key(Keys::interruption);
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
