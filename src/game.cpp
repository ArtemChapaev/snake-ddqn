#include "game.h"

Game::Game(std::string file) : filename(file), highest_score(0), death_score(0) {
    ConsoleUI::off_cursor();
}

int Game::start_level(unsigned level_number) {
    parser(settings, filename);

    unsigned snake_length = kSnakeLength;
    if (!settings.reset_length) {
        snake_length = death_score + kSnakeLength; // bcs for last level: death_score = snake.size() - SNAKE_LENGTH
    }
    Snake snake(settings, snake_length);
    KeyboardControl control(settings);
    ConsoleUI console;
    MapModel map_model(settings);
    MapView map_view(map_model, settings);

    bool is_exit = false;
    unsigned eaten_bonuses_number = 0;

    unsigned moves_number = 0;
    unsigned moves_number_after_bonus = 0;
    float speed_of_bonus = 1.0;

    map_model.put_snake(snake);

    map_model.generate_bonus(bonus);
    if (settings.bonus_apples) {
        map_model.generate_bonus(antibonus);
        map_model.generate_bonus(speed_bonus);
        map_model.generate_bonus(speed_antibonus);
    }

    console.set_cursor(1, 1);
    console.clear_full_display();

    map_view.print();

    while (!is_exit) {
        Keys last_dir = snake.get_direction();
        Keys new_key = control.read_key(last_dir);
        if (new_key == Keys::interruption) {
            switch (pause_game()) {
                case PauseMenu::resume_code:
                    console.clear_full_display();
                    continue;
                case PauseMenu::restart_code:
                    return PauseMenu::restart_code;
                case PauseMenu::exit_code:
                    return PauseMenu::exit_code;
            }
        }

        if (last_dir != new_key && control.check_direction(last_dir, new_key)) {
            snake.set_direction(new_key);
        }

        Position next_cell = snake.get_next();
        switch (map_model.check_cell(next_cell.get_y(), next_cell.get_x())) {
            case Cell::bonus: {
                Position last_tail = snake.move();
                snake.increase_length(last_tail);

                map_model.put_snake(snake);
                map_model.generate_bonus(bonus);

                ++eaten_bonuses_number;
                break;
            }
            case Cell::antibonus: {
                Position last_tail = snake.move();
                map_model.clear_cell(last_tail);

                last_tail = snake.decrease_length();
                map_model.clear_cell(last_tail);

                map_model.put_snake(snake);
                map_model.generate_bonus(antibonus);

                if (snake.get_snake().size() == 0) {
                    is_exit = true;
                } else {
                    ++eaten_bonuses_number; // if game over with len = 0, the level is not passed
                }
                break;
            }
            case Cell::speed_bonus: {
                Position last_tail = snake.move();
                map_model.clear_cell(last_tail);

                map_model.put_snake(snake);
                map_model.generate_bonus(speed_bonus);

                moves_number_after_bonus = 0;
                speed_of_bonus = kBonusSpeedForSnake;

                ++eaten_bonuses_number;
                break;
            }
            case Cell::speed_antibonus: {
                Position last_tail = snake.move();
                map_model.clear_cell(last_tail);

                map_model.put_snake(snake);
                map_model.generate_bonus(speed_antibonus);

                moves_number_after_bonus = 0;
                speed_of_bonus = 1.0 / kBonusSpeedForSnake;

                ++eaten_bonuses_number;
                break;
            }
            case Cell::snake: {
                if (snake.get_tail() == next_cell) {
                    snake.move(); // without clear_cell, bcs there will be the head in this cell in next move
                    map_model.put_snake(snake);
                    break;
                }
                // falls down
            }
            case Cell::wall: {
                is_exit = true;
                break;
            }
            case Cell::teleport: {
                Position last_tail = snake.relocate_snake(settings);
                map_model.clear_cell(last_tail);

                map_model.put_snake(snake);
                break;
            }
            case Cell::empty: {
                Position last_tail = snake.move();
                map_model.clear_cell(last_tail);

                map_model.put_snake(snake);
                break;
            }
        }

        console.set_cursor(1, 1);

        map_view.print();

        death_score = (int) (snake.get_snake().size() - kSnakeLength) > 0 ? snake.get_snake().size() - kSnakeLength : 0;
        highest_score = death_score > highest_score ? death_score : highest_score;

        if (settings.score) {
            unsigned score = death_score;
            console.clear_score_line(settings);
            console.set_cursor(settings.map_width + 1, settings.map_length - 5);
            std::cout << "SCORE: " << score<< std::endl;
        }

        if (moves_number_after_bonus == kMovesForSpeedBonus) {
            speed_of_bonus = 1.0;
        }

        ++moves_number;
        ++moves_number_after_bonus;

        usleep(kMovePause / snake.get_speed_coef() / speed_of_bonus / LEVEL_SPEED(level_number));
        if (eaten_bonuses_number == kBonusesForNewLevel) {
            console.clear_full_display();
            map_view.print_walls();
            console.set_cursor(settings.map_length / 2, settings.map_width - kWinString.size() / 2);
            std::cout << kWinString << std::flush;
            return 0;
        }
    }
    return 1;
}

int Game::pause_game() {
    std::stack<std::unique_ptr<Menu>> menus; // stores opened menus hierarchy

    unsigned string_num = 0; // stores which menu option is selected
    unsigned prev_string_num = string_num;
    int return_code = 0;

    Menu *m = new PauseMenu(filename);
    menus.push(std::unique_ptr<Menu>(m));
    menus.top().get()->draw(string_num);
    while (return_code == 0) {
        return_code = menus.top().get()->update(string_num, menus);
        if (string_num != prev_string_num) {
            menus.top().get()->draw(string_num);
            prev_string_num = string_num;
        }
    }
    return return_code;
}

int Game::start_game(bool random_apples) {
    auto start_time = std::chrono::high_resolution_clock::now();
    int level_exit_code = 0;
    unsigned level_number = 0;

    random_apples ? srand(time(0)) : srand(1);

    while (level_exit_code == 0) {
        level_exit_code = start_level(level_number);
        usleep(kLevelPause);
    }

    std::chrono::duration<float> duration = std::chrono::high_resolution_clock::now() - start_time;
    game_time = duration.count();

    write_to_leaderboard();
    return level_exit_code;
}

int Game::write_to_leaderboard() {
    std::ifstream out_file(kLeaderboardFile);
    std::vector<std::tuple<std::string, unsigned>> leaderboard;
    std::string data, score;

    if (out_file.good()) {
        while (!out_file.eof()) {
            getline(out_file, data, ';');
            if (data.empty()) {
                continue;
            }

            getline(out_file, score);
            leaderboard.emplace_back(data, stoi(score));
        }
        out_file.close();
    }

    if (leaderboard.size() == 10 && std::get<1>(leaderboard[9]) < highest_score) {
        leaderboard.pop_back();
    }

    auto now = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(now);
    data = std::string(std::ctime(&end_time));
    data.pop_back();

    auto temp = std::make_tuple(data, highest_score);

    int i = 0;
    while (i < leaderboard.size() && std::get<1>(leaderboard[i]) >= highest_score) { // finding the right place
        ++i;
    }

    for (; i < leaderboard.size(); ++i) {
        auto temp_2 = leaderboard[i];
        leaderboard[i] = temp;
        temp = temp_2;
    }
    leaderboard.push_back(temp);

    std::ofstream in_file(kLeaderboardFile);
    if (!in_file.is_open()) {
        return -1;
    }

    for (auto entry: leaderboard) {
        in_file << std::get<0>(entry) << ';' << std::to_string(std::get<1>(entry)) << '\n';
    }
    in_file.close();
    return 0;
}

int Game::print_deathscreen() {
    ConsoleUI console;
    console.set_cursor(0, 0);
    console.clear_full_display();

    for (int j = 1; j <= settings.map_width; j++) {
        for (int i = 1; i <= settings.map_length; i++) {
            if (i == 1 || i == settings.map_length || j == 1 || j == settings.map_width) {
                console.set_cursor(j, i * 2 - 1);
                std::cout << '#';
            }
        }
    }

    console.set_cursor(settings.map_length / 2 - 1, settings.map_width / 2);
    std::cout << "Play time: " << game_time << " seconds" << std::endl;

    if (settings.bonus_apples) {
        console.set_cursor(settings.map_length / 2, settings.map_width / 2);
        std::cout << "Highest score: " << highest_score << std::endl;

        console.set_cursor(settings.map_length / 2 + 1, settings.map_width / 2);
        std::cout << "Final score: " << death_score << std::endl;

        console.set_cursor(settings.map_length + 1, 1);
        return 0;
    }

    console.set_cursor(settings.map_length / 2, settings.map_width / 2);
    std::cout << "Final score: " << death_score << std::endl;

    console.set_cursor(settings.map_length + 1, 1);
    return 0;
}

Game::~Game() {
    ConsoleUI::on_cursor();
}
