#include "menu.h"

Menu::Menu(std::string file) : filename(file) {
    ConsoleUI::off_cursor();
    parser(settings, filename);
}

// MainMenu::MainMenu(std::string file) : filename(file) {
//     options_count = exit;
//     parser(settings, filename);
// }

MainMenu::MainMenu(std::string file) : Menu(file) {
    options_count = exit;
}

void MainMenu::pure_draw() {
    std::cout << "\033[17;33HStart game" << std::endl;
    std::cout << "\033[18;33HLeaderboard" << std::endl;
    std::cout << "\033[19;33HSettings" << std::endl;
    std::cout << "\033[20;33HCredits" << std::endl;
    std::cout << "\033[21;33HExit" << std::endl;
}

void MainMenu::draw(int _stringNum) {

    ConsoleUI::off_cursor();
    ConsoleUI console;
    console.clear_full_display();
    console.set_cursor(3,1);

    print_logo();
    pure_draw();

    switch (_stringNum) {
        case start:
            std::cout << "\033[17;33H\033[4mStart game\033[0m" << std::endl;
            break;
        case leaderboard:
            std::cout << "\033[18;33H\033[4mLeaderboard\033[0m" << std::endl;
            break;
        case setings:
            std::cout << "\033[19;33H\033[4mSettings\033[0m" << std::endl;
            break;
        case credits:
            std::cout << "\033[20;33H\033[4mCredits\033[0m" << std::endl;
            break;
        case exit:
            std::cout << "\033[21;33H\033[4mExit\033[0m" << std::endl;
            break;
    }

}

unsigned MainMenu::update(int &_stringNum, std::stack<std::unique_ptr<Menu>> &_menus) {
    bool is_exit = false;
    KeyboardControl control(settings);

    while (!is_exit) {
        // initializes with right direction argument bcs there is no right direction option in menu
        Keys key = control.read_key(right);
        is_exit = true;
        switch (key) {
            case up:
                _stringNum > 0 ? _stringNum -= 1 : _stringNum = options_count;
                break;
            case down:
                _stringNum < options_count ? _stringNum += 1 : _stringNum = 0;
                break;
            case enter:
                if (_stringNum == start) { // start game
                    Game game(filename);
                    game.start_game(false);
                    game.print_deathscreen();
                    sleep(3);
                    _menus.top().get()->draw(_stringNum);
                } 
                else if (_stringNum == leaderboard) { // open leaderboard
                    _stringNum = 0;
                    Menu* m = new LeaderboardMenu(filename);
                    _menus.push(std::unique_ptr<Menu>(m));
                    _menus.top().get()->draw(_stringNum);
                }
                else if (_stringNum == setings) { // open settings
                    _stringNum = 0;
                    Menu* m = new SettingsGeneralMenu(filename);
                    _menus.push(std::unique_ptr<Menu>(m));
                    _menus.top().get()->draw(_stringNum);
                }
                else if (_stringNum == credits) { // show credits
                    Menu* m = new TitlesMenu(filename);
                    _menus.push(std::unique_ptr<Menu>(m));
                    _menus.top().get()->draw(_stringNum);
                }
                else if (_stringNum == exit) { // exit
                    ConsoleUI::on_cursor();
                    std::cout << "\033[1;1H";
                    std::cout << "\033[2J";
                    return 1;
                }
                break;
            default:
                is_exit = false;
                usleep(SLEEP_TIME);
            }
    }
    return 0;
}

//************//

LeaderboardMenu::LeaderboardMenu(std::string file) : Menu(file) {
    options_count = exit;
}

void LeaderboardMenu::pure_draw() {
    std::cout << "\033[17;46HTo be updated!" << std::endl;
    std::cout << "\033[18;46HExit" << std::endl;
}

void LeaderboardMenu::draw(int _stringNum) {
    ConsoleUI::off_cursor();
    ConsoleUI console;
    console.clear_full_display();
    console.set_cursor(3,1);

    print_logo();

    switch(_stringNum) {
        case tbu:
            pure_draw();
            std::cout << "\033[17;46H\033[4mTo be updated!\033[0m" << std::endl;
            break;
        case exit:
            pure_draw();
            std::cout << "\033[18;46H\033[4mExit\033[0m" << std::endl;
            break;
    }
}

unsigned LeaderboardMenu::update(int &_stringNum, std::stack<std::unique_ptr<Menu>> &_menus) {
    bool is_exit = false;
    KeyboardControl control(settings);

    while (!is_exit) {
        Keys key = control.read_key(right);
        is_exit = true;

        switch (key) {
            case up:
                _stringNum > 0 ? _stringNum -= 1 : _stringNum = options_count;
                break;
            case down:
                _stringNum < options_count ? _stringNum += 1 : _stringNum = 0;
                break;
            case enter:
                if (_stringNum == tbu) { // speed option
                    // TODO
                }
                else if (_stringNum == exit) { // exit
                    _stringNum = 0;
                    _menus.pop();
                    _menus.top().get()->draw(_stringNum);
                }
                break;
            default:
                is_exit = false;
                usleep(SLEEP_TIME);
        }
    }
    return 0;
}


//************//



SettingsGeneralMenu::SettingsGeneralMenu(std::string file) : Menu(file) {
    options_count = exit;
}

void SettingsGeneralMenu::pure_draw() {
    std::cout << "\033[17;46HSnake settings" << std::endl;
    std::cout << "\033[18;46HMap settings" << std::endl;
    std::cout << "\033[19;46HGraphic settings" << std::endl;
    std::cout << "\033[20;46HControl settings" << std::endl;
    std::cout << "\033[21;46HExit" << std::endl;
}

void SettingsGeneralMenu::draw(int _stringNum) {
    ConsoleUI::off_cursor();
    ConsoleUI console;
    console.clear_full_display();
    console.set_cursor(3,1);

    print_logo();
    pure_draw();

    switch(_stringNum) {
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

unsigned SettingsGeneralMenu::update(int &_stringNum, std::stack<std::unique_ptr<Menu>> &_menus) {
    bool is_exit = false;
    KeyboardControl cntrl(settings);

    while (!is_exit) {
        Keys key = cntrl.read_key(right);
        is_exit = true;

        switch (key) {
            case up:
                _stringNum > 0 ? _stringNum -= 1 : _stringNum = options_count;
                break;
            case down:
                _stringNum < options_count ? _stringNum += 1 : _stringNum = 0;
                break;
            case enter:
                if (_stringNum == snake) { // snake settings
                    _stringNum = 0;
                    Menu* m = new SettingsSnakeMenu(filename);
                    _menus.push(std::unique_ptr<Menu>(m));
                    _menus.top().get()->draw(_stringNum);
                }
                else if (_stringNum == map) { // map settings
                    _stringNum = 0;
                    Menu* m = new SettingsMapMenu(filename);
                    _menus.push(std::unique_ptr<Menu>(m));
                    _menus.top().get()->draw(_stringNum);
                }
                else if (_stringNum == graphic) { // graphic settings
                    _stringNum = 0;
                    Menu* m = new SettingsGraphicMenu(filename);
                    _menus.push(std::unique_ptr<Menu>(m));
                    _menus.top().get()->draw(_stringNum);
                }
                else if (_stringNum == control) { // graphic settings
                    _stringNum = 0;
                    Menu* m = new SettingsControlMenu(filename);
                    _menus.push(std::unique_ptr<Menu>(m));
                    _menus.top().get()->draw(_stringNum);
                }
                else if (_stringNum == exit) { // exit
                    _stringNum = 0;
                    _menus.pop();
                    _menus.top().get()->draw(_stringNum);
                }
                break;
            default:
                is_exit = false;
                usleep(SLEEP_TIME);
        }
    }
    return 0;
}

//************//

SettingsSnakeMenu::SettingsSnakeMenu(std::string file) : Menu(file) {
    options_count = exit;
}

void SettingsSnakeMenu::pure_draw() {
    std::cout << "\033[17;46HSpeed:" << std::endl;
    std::cout << "\033[18;46HReset length at new level:" << std::endl;
    std::cout << "\033[19;46HExit" << std::endl;
}

void SettingsSnakeMenu::draw(int _stringNum) {
    ConsoleUI::off_cursor();
    ConsoleUI console;
    
    console.clear_full_display();
    console.set_cursor(3,1);

    print_logo();
    pure_draw();

    switch (_stringNum) {
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

unsigned SettingsSnakeMenu::update(int &_stringNum, std::stack<std::unique_ptr<Menu>> &_menus) {
    bool is_exit = false;
    KeyboardControl control(settings);

    while (!is_exit) {
        Keys key = control.read_key(right);
        is_exit = true;

        switch (key) {
            case up:
                _stringNum > 0 ? _stringNum -= 1 : _stringNum = options_count;
                break;
            case down:
                _stringNum < options_count ? _stringNum += 1 : _stringNum = 0;
                break;
            case enter:
                if (_stringNum == speed) { // speed option
                    // TODO
                }
                else if (_stringNum == reset_length) { // reset length option
                    // TODO
                }
                else if (_stringNum == exit) { // exit
                    _stringNum = 0;
                    _menus.pop();
                    _menus.top().get()->draw(_stringNum);
                }
                break;
            default:
                is_exit = false;
                usleep(SLEEP_TIME);
        }
    }

    return 0;
}

//************//

SettingsMapMenu::SettingsMapMenu(std::string file) : Menu(file) {
    options_count = exit;
}

void SettingsMapMenu::pure_draw() {
    std::cout << "\033[17;46HMap length: " << std::endl;
    std::cout << "\033[18;46HMap width: " << std::endl;
    std::cout << "\033[19;46HEnable solid walls: " << std::endl;
    std::cout << "\033[20;46HEnable bonus apples: " << std::endl;
    std::cout << "\033[21;46HEnable teleports: " << std::endl;
    std::cout << "\033[22;46HShow score: " << std::endl;
    std::cout << "\033[23;46HExit" << std::endl;
}

void SettingsMapMenu::draw(int _stringNum) {
    ConsoleUI::off_cursor();
    ConsoleUI console;
    console.clear_full_display();
    console.set_cursor(3,1);

    print_logo();
    pure_draw();

    switch (_stringNum) {
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

unsigned SettingsMapMenu::update(int &_stringNum, std::stack<std::unique_ptr<Menu>> &_menus) {
    bool is_exit = false;
    KeyboardControl control(settings);

    while (!is_exit) {
        Keys key = control.read_key(right);
        is_exit = true;

        switch (key) {
            case up:
                _stringNum > 0 ? _stringNum -= 1 : _stringNum = options_count;
                break;
            case down:
                _stringNum < options_count ? _stringNum += 1 : _stringNum = 0;
                break;
            case enter:
                if (_stringNum == length) { // map length option
                    // TODO
                }
                else if (_stringNum == width) { // map width option
                    // TODO
                }
                else if (_stringNum == solid_walls) { // enable solid walls option
                    // TODO
                }
                else if (_stringNum == bonus_apples) { // enable bonus apples option
                    // TODO
                }
                else if (_stringNum == teleports) { // enable teleports option
                    // TODO
                }
                else if (_stringNum == show_score) { // show score option
                    // TODO
                }
                else if (_stringNum == exit) { // exit option
                    _stringNum = 0;
                    _menus.pop();
                    _menus.top().get()->draw(_stringNum);
                }
                break;
            default:
                is_exit = false;
                usleep(SLEEP_TIME);
        }
    }
    return 0;
}

//************//

SettingsControlMenu::SettingsControlMenu(std::string file) : Menu(file) {
    options_count = exit;
}

void SettingsControlMenu::pure_draw() {
    std::cout << "\033[17;46HUp key: " << std::endl;
    std::cout << "\033[18;46HDown key: " << std::endl;
    std::cout << "\033[19;46HLeft key: " << std::endl;
    std::cout << "\033[20;46HRight key: " << std::endl;
    std::cout << "\033[21;46HPause key: " << std::endl;
    std::cout << "\033[22;46HEnter key: " << std::endl;
    std::cout << "\033[23;46HExit" << std::endl;
}

void SettingsControlMenu::draw(int _stringNum) {
    ConsoleUI::off_cursor();
    ConsoleUI console;
    
    console.clear_full_display();
    console.set_cursor(3,1);

    print_logo();
    pure_draw();

    switch (_stringNum) {
        case up:
            std::cout << "\033[17;46H\033[4mUp key: \033[0m" << std::endl;
            break;
        case down:
            std::cout << "\033[18;46H\033[4mDown key: \033[0m" << std::endl;
            break;
        case left:
            std::cout << "\033[19;46H\033[4mLeft key: \033[0m" << std::endl;
            break;
        case rightt:
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

unsigned SettingsControlMenu::update(int &_stringNum, std::stack<std::unique_ptr<Menu>> &_menus) {
    bool is_exit = false;
    KeyboardControl control(settings);

    while (!is_exit) {    
        Keys key = control.read_key(right);
        is_exit = true;

        switch (key) {
            case up:
                _stringNum > 0 ? _stringNum -= 1 : _stringNum = options_count;
                break;
            case down:
                _stringNum < options_count ? _stringNum += 1 : _stringNum = 0;
                break;
            case enter:
                if (_stringNum == up) { // up key option
                    // TODO
                }
                else if (_stringNum == down) { // down key option
                    // TODO
                }
                else if (_stringNum == left) { // left key option
                    // TODO
                }
                else if (_stringNum == rightt) { // right key option
                    // TODO
                }
                else if (_stringNum == pause) { // pause key option
                    // TODO
                }
                else if (_stringNum == enter) { // enter key option
                    // TODO
                }
                else if (_stringNum == exit) { // exit option
                    _stringNum = 0;
                    _menus.pop();
                    _menus.top().get()->draw(_stringNum);
                }
                break;
            default:
                is_exit = false;
                usleep(SLEEP_TIME);
        }
    }
    return 0;
}

//************//

SettingsGraphicMenu::SettingsGraphicMenu(std::string file) : Menu(file) {
    options_count = exit;
}

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

void SettingsGraphicMenu::draw(int _stringNum) {
    ConsoleUI::off_cursor();
    ConsoleUI console;
    console.clear_full_display();

    print_logo();
    pure_draw();

    switch (_stringNum) {
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

unsigned SettingsGraphicMenu::update(int &_stringNum, std::stack<std::unique_ptr<Menu>> &_menus) {
    bool is_exit = false;
    KeyboardControl control(settings);

    while (!is_exit) {
        Keys key = control.read_key(right);
        is_exit = true;

        switch (key) {
            case up:
                _stringNum > 0 ? _stringNum -= 1 : _stringNum = options_count;
                break;
            case down:
                _stringNum < options_count ? _stringNum += 1 : _stringNum = 0;
                break;
            case enter:
                if (_stringNum == snake) { // snake color option
                    // TODO
                }
                else if (_stringNum == empty_block) { // empty block color option
                    // TODO
                }
                else if (_stringNum == wall) { // wall color option
                    // TODO
                }
                else if (_stringNum == teleport) { // teleport color option
                    // TODO
                }
                else if (_stringNum == bonus) { // bonus color option
                    // TODO
                }
                else if (_stringNum == anti_bonus) { // antibonus color option
                    // TODO
                }
                else if (_stringNum == speed_bonus) { // speed bonus color option
                    // TODO
                }
                else if (_stringNum == anti_speed_bonus) { // speed antibonus color option
                    // TODO
                }
                else if (_stringNum == exit) { // exit
                    _stringNum = 0;
                    _menus.pop();
                    _menus.top().get()->draw(_stringNum);
                }
                break;
            default:
                is_exit = false;
                usleep(SLEEP_TIME);
        }
    }
    return 0;
}

//************//

TitlesMenu::TitlesMenu(std::string file) : Menu(file) {
}

void TitlesMenu::pure_draw() {

}

unsigned TitlesMenu::update(int &_stringNum, std::stack<std::unique_ptr<Menu>> &_menus) {
    bool is_exit = false;
    KeyboardControl control(settings);

    while (!is_exit) {
        Keys key = control.read_key(right);
        is_exit = true;

        switch (key) {
            case enter:
                _stringNum = 0;
                _menus.pop();
                _menus.top().get()->draw(_stringNum);
                break;
            default:
                is_exit = false;
                usleep(SLEEP_TIME);
        }
    }
    return 0;
}

void TitlesMenu::draw(int _string) {
    ConsoleUI console;
    console.clear_full_display();
    console.set_cursor(3,1);

    print_logo();

}