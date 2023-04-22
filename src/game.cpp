#include "game.h"

Game::Game(std::string file) : filename(file), highest_score(0), death_score(0), pause_time(0) {
    ConsoleUI::off_cursor();
}

int Game::start_game(bool random_apples) {
    auto start_time = std::chrono::high_resolution_clock::now();
    int level_exit_code = 0;
    unsigned level_number = 1;

    parser(settings, filename);

    random_apples ? srand(time(0)) : srand(1);

    while (level_exit_code == 0) {
        if (settings.ai_mode == 0) {
            level_exit_code = start_level(level_number);
        } else if (settings.ai_mode == 1) {
            level_exit_code = start_ai_learning(settings.epochs);
        } else if (settings.ai_mode == 2) {
            level_exit_code = start_ai_game(settings.epochs);
        }
        ++level_number;
        usleep(kLevelPause);
    }

    std::chrono::duration<float> duration = std::chrono::high_resolution_clock::now() - start_time;
    game_time = duration.count();

    write_to_leaderboard();
    print_deathscreen();
    sleep(3);
    return level_exit_code;
}

// method for manual control
int Game::start_level(unsigned level_number) {
    unsigned snake_length = kSnakeLength;
    if (!settings.reset_length) {
        // bcs for last level: death_score = snake.size() - kSnakeLength
        snake_length = death_score + kSnakeLength;
    }

    Snake snake(settings, snake_length);
    KeyboardControl control(settings);
    ConsoleUI console;
    MapModel map_model = read_map_from_file(settings);
    MapView map_view(map_model, settings);

    bool is_exit = false;
    unsigned moves_number_after_bonus = 0;
    unsigned moves_number_after_error = 0;
    float speed_of_bonus = 1.0;

    map_model.put_snake(snake);

    map_model.generate_bonus(bonus_c);
    if (settings.bonus_apples) {
        map_model.generate_bonus(antibonus_c);
        map_model.generate_bonus(speed_bonus_c);
        map_model.generate_bonus(speed_antibonus_c);
    }

    console.set_cursor(1, 1);
    console.clear_full_display();

    map_view.print();

    while (!is_exit) {
        Keys last_dir = snake.get_direction();
        Keys new_key = control.read_key(last_dir);

        if (new_key == Keys::error || new_key == Keys::enter || new_key == Keys::teleport ||
            new_key == Keys::wall || new_key == Keys::empty) {
            moves_number_after_error = 0;
            print_control_error_screen();
        } else if (new_key == Keys::interruption) {
            switch (pause_game()) {
                case PauseMenu::resume_code:
                    console.clear_full_display();
                    continue;
                case PauseMenu::restart_code:
                    return PauseMenu::restart_code;
                case PauseMenu::exit_code:
                    return PauseMenu::exit_code;
            }
        } else if (last_dir != new_key && control.check_direction(last_dir, new_key)) {
            snake.set_direction(new_key);
        }

        Position next_cell = snake.get_next();
        switch (map_model.check_cell(next_cell.get_y(), next_cell.get_x())) {
            case Cell::bonus_c: {
                Position last_tail = snake.move();
                snake.increase_length(last_tail);

                map_model.put_snake(snake);
                map_model.generate_bonus(bonus_c);
                break;
            }
            case Cell::antibonus_c: {
                Position last_tail = snake.move();
                map_model.clear_cell(last_tail);

                last_tail = snake.decrease_length();
                map_model.clear_cell(last_tail);

                map_model.put_snake(snake);
                map_model.generate_bonus(antibonus_c);

                if (snake.get_length() == 0) {
                    is_exit = true;
                }
                break;
            }
            case Cell::speed_bonus_c: {
                Position last_tail = snake.move();
                map_model.clear_cell(last_tail);

                map_model.put_snake(snake);
                map_model.generate_bonus(speed_bonus_c);

                moves_number_after_bonus = 0;
                speed_of_bonus = kBonusSpeedForSnake;
                break;
            }
            case Cell::speed_antibonus_c: {
                Position last_tail = snake.move();
                map_model.clear_cell(last_tail);

                map_model.put_snake(snake);
                map_model.generate_bonus(speed_antibonus_c);

                moves_number_after_bonus = 0;
                speed_of_bonus = 1.0 / kBonusSpeedForSnake;
                break;
            }
            case Cell::snake_c: {
                if (snake.get_tail() == next_cell) {
                    snake.move();  // without clear_cell, bcs there will be the head in this cell in next move
                    map_model.put_snake(snake);
                    break;
                }
                // falls down
            }
            case Cell::wall_c: {
                is_exit = true;
                break;
            }
            case Cell::teleport_c: {
                Position last_tail = snake.relocate_snake(settings);
                map_model.clear_cell(last_tail);

                map_model.put_snake(snake);
                break;
            }
            case Cell::empty_c: {
                Position last_tail = snake.move();
                map_model.clear_cell(last_tail);

                map_model.put_snake(snake);
                break;
            }
            default:
                break;
        }

        console.set_cursor(1, 1);

        map_view.print();

        death_score =
            static_cast<int>(snake.get_length() - kSnakeLength) > 0 ? snake.get_length() - kSnakeLength : 0;

        highest_score = death_score > highest_score ? death_score : highest_score;

        if (settings.score) {
            unsigned score = death_score;
            console.clear_line(settings.map_width + 1);
            console.set_cursor(settings.map_width + 1, settings.map_length - 5);
            std::cout << "SCORE: " << score << std::endl;
        }

        if (moves_number_after_bonus == kMovesForSpeedBonus) {
            speed_of_bonus = 1.0;
        }

        if (moves_number_after_error ==
            kMovesAfterControlError) {  // if enough moves passed after control error
            console.clear_line(settings.map_width + 3);
        }

        ++moves_number_after_bonus;
        ++moves_number_after_error;

        usleep(kMovePause / snake.get_speed_coef() / speed_of_bonus / LEVEL_SPEED(level_number - 1));

        if (death_score == kBonusesForNewLevel * level_number) {
            console.clear_full_display();
            map_view.print_walls();
            console.set_cursor(settings.map_length / 2, settings.map_width - kWinString.size() / 2);
            std::cout << kWinString << std::flush;
            return 0;
        }
    }
    return 1;
}

int Game::start_ai_learning(unsigned episodes_total) {
    unsigned episodes_count = 0;
    double total_reward = 0;
    unsigned output_line = 0;

    std::vector<int> layers = {LAYERS};
    AiControl ai(layers);
    ai.load_network_hyperparameters();

    ConsoleUI console;
    console.clear_full_display();
    while (episodes_count < episodes_total || episodes_total == 0) {
        unsigned snake_length = kSnakeLength;

        // main creatures
        Snake snake(settings, snake_length);
        KeyboardControl control(settings);
        MapModel map_model = read_map_from_file(settings);

        // variables for AI
        bool is_first_iteration = true;
        State last_state;
        Keys action = Keys::right;
        double reward = 0.0;

        // game preparing
        bool is_exit = false;
        map_model.put_snake(snake);
        map_model.generate_bonus(bonus_c);

        while (!is_exit) {
            Keys pressed_key = control.read_key(Keys::up);  // for pause
            if (pressed_key == Keys::interruption) {
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

            State state = get_state(map_model, snake);

            if (is_first_iteration) {
                is_first_iteration = false;
            } else {
                ai.train_nn(last_state, action, reward, state);
                // last_direction == action
                Keys new_key = ai.get_direction(last_state, action);
                snake.set_direction(new_key);
                reward = 0.0;
            }
            action = snake.get_direction();
            last_state = state;

            Position next_cell = snake.get_next();
            switch (map_model.check_cell(next_cell.get_y(), next_cell.get_x())) {
                case Cell::bonus_c: {
                    Position last_tail = snake.move();
                    snake.increase_length(last_tail);

                    map_model.put_snake(snake);
                    map_model.generate_bonus(bonus_c);
                    reward = kRewardPositive;
                    total_reward += kRewardPositive;
                    break;
                }
                    // no need for bonuses when learning AI
                case Cell::antibonus_c:
                case Cell::speed_bonus_c:
                case Cell::teleport_c:
                case Cell::speed_antibonus_c: {
                    break;
                }
                case Cell::snake_c: {
                    if (snake.get_tail() == next_cell) {
                        snake.move();  // without clear_cell, bcs there will be the head in this cell in next
                        // move
                        map_model.put_snake(snake);
                        break;
                    }
                    // falls down
                }
                case Cell::wall_c: {
                    reward = kRewardNegative;
                    total_reward += kRewardNegative;
                    is_exit = true;
                    episodes_count++;
                    break;
                }
                case Cell::empty_c: {
                    Position last_tail = snake.move();
                    map_model.clear_cell(last_tail);

                    map_model.put_snake(snake);
                    break;
                }
                default:
                    break;
            }

            // metrics for AI
            if (episodes_count % kEpisodesForOutput == kEpisodesForOutput - 1 && is_exit) {
                console.clear_line(output_line + 5);
                console.set_cursor(output_line + 5, settings.map_length - 15);
                std::cout << (episodes_count + 1) / kEpisodesForOutput << ") Average reward for last "
                          << kEpisodesForOutput
                          << " episodes: " << total_reward / kEpisodesForOutput / kRewardPositive;

                output_line = (output_line + 1) % 10;
                total_reward = 0.0;

                console.clear_line(15);
                console.set_cursor(15, settings.map_length - 5);
                std::cout << "EPOCH: " << episodes_count + 1 << " OF "
                          << (episodes_total == 0 ? "∞" : std::to_string(episodes_total)) << std::flush;
            }

            if (episodes_count % kEpisodesForSaveHyperparams == kEpisodesForSaveHyperparams - 1 && is_exit) {
                ai.save_network_hyperparameters();
            }
        }
        State state = get_state(map_model, snake);
        ai.train_nn(last_state, action, reward, state);
    }

    return 1;
}

int Game::start_ai_game(unsigned episodes_total) {
    unsigned episodes_count = 0;

    std::vector<int> layers = {LAYERS};
    AiControl ai(layers);
    ai.load_network_hyperparameters();

    ConsoleUI console;
    while (episodes_count < episodes_total || episodes_total == 0) {
        unsigned snake_length = kSnakeLength;

        // main creatures
        Snake snake(settings, snake_length);
        KeyboardControl control(settings);
        MapModel map_model = read_map_from_file(settings);
        MapView map_view(map_model, settings);

        // part of neural network
        bool is_first_iteration = true;
        State last_state;
        Keys action = Keys::right;
        double reward = 0;

        // game process variables
        bool is_exit = false;

        // game preparing
        map_model.put_snake(snake);

        map_model.generate_bonus(bonus_c);
        if (settings.bonus_apples) {
            map_model.generate_bonus(antibonus_c);
            map_model.generate_bonus(speed_bonus_c);
            map_model.generate_bonus(speed_antibonus_c);
        }

        console.set_cursor(1, 1);
        console.clear_full_display();
        map_view.print();

        while (!is_exit) {
            Keys pressed_key = control.read_key(Keys::up);  // for pause
            if (pressed_key == Keys::interruption) {
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

            State state = get_state(map_model, snake);

            if (is_first_iteration) {
                is_first_iteration = false;
            } else {
                Keys new_key = ai.get_direction(last_state, action);
                snake.set_direction(new_key);
                reward = 0.0;
            }
            action = snake.get_direction();
            last_state = state;

            Position next_cell = snake.get_next();
            switch (map_model.check_cell(next_cell.get_y(), next_cell.get_x())) {
                case Cell::bonus_c: {
                    Position last_tail = snake.move();
                    snake.increase_length(last_tail);

                    map_model.put_snake(snake);
                    map_model.generate_bonus(bonus_c);
                    reward = kRewardPositive;
                    break;
                }
                    // no need for bonuses when learning AI
                case Cell::antibonus_c:
                case Cell::speed_bonus_c:
                case Cell::teleport_c:
                case Cell::speed_antibonus_c: {
                    break;
                }
                case Cell::snake_c: {
                    if (snake.get_tail() == next_cell) {
                        snake.move();  // without clear_cell, bcs there will be the head in this cell in next
                        // move
                        map_model.put_snake(snake);
                        break;
                    }
                    // falls down
                }
                case Cell::wall_c: {
                    reward = kRewardNegative;
                    is_exit = true;
                    episodes_count++;
                    break;
                }
                case Cell::empty_c: {
                    Position last_tail = snake.move();
                    map_model.clear_cell(last_tail);

                    map_model.put_snake(snake);
                    break;
                }
                default:
                    break;
            }

            if (settings.score) {
                console.clear_line(settings.map_width + 1);
                console.set_cursor(settings.map_width + 1, settings.map_length - 7);
                std::cout << "CURRENT SCORE: " << snake.get_length() - kSnakeLength;
            }

            // metrics for AI
            console.clear_line(settings.map_width + 2);
            console.set_cursor(settings.map_width + 2, settings.map_length - 7);
            std::cout << "EPOCH: " << episodes_count + 1 << " OF "
                      << (episodes_total == 0 ? "∞" : std::to_string(episodes_total));

            console.set_cursor(1, 1);
            map_view.print();

            usleep(200000);

            if (episodes_count % kEpisodesForSaveHyperparams == kEpisodesForSaveHyperparams - 1 && is_exit) {
                ai.save_network_hyperparameters();
            }
        }
    }

    return 1;
}

int Game::pause_game() {
    auto pause_start_time = std::chrono::high_resolution_clock::now();

    std::stack<std::unique_ptr<Menu>> menus;  // stores opened menus hierarchy

    unsigned string_num = 0;  // stores which menu option is selected
    unsigned prev_string_num = string_num;
    int return_code = 0;

    Menu* m = new PauseMenu(filename);
    menus.push(std::unique_ptr<Menu>(m));
    menus.top().get()->draw(string_num);
    while (return_code == 0) {
        return_code = menus.top().get()->update(string_num, menus);
        if (string_num != prev_string_num) {
            menus.top().get()->draw(string_num);
            prev_string_num = string_num;
        }
    }

    std::chrono::duration<float> pause_duration =
        std::chrono::high_resolution_clock::now() - pause_start_time;
    pause_time += pause_duration.count();

    return return_code;
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

    if (leaderboard.size() == 10) {
        if (std::get<1>(leaderboard[9]) < highest_score) {
            leaderboard.pop_back();
        } else {
            return 0;
        }
    }

    auto now = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(now);
    data = std::string(std::ctime(&end_time));
    data.pop_back();

    auto temp = std::make_tuple(data, highest_score);

    int i = 0;
    while (i < leaderboard.size() &&
           std::get<1>(leaderboard[i]) >= highest_score) {  // finding the right place
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

    for (auto entry : leaderboard) {
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

    console.set_cursor(settings.map_length / 2 - 1, settings.map_width - kPlayTimeStringLength / 2);
    std::cout << "Play time: " << game_time - pause_time << " seconds" << std::endl;

    if (settings.bonus_apples) {
        console.set_cursor(settings.map_length / 2, settings.map_width - kHighScoreStringLength / 2);
        std::cout << "Highest score: " << highest_score << std::endl;

        console.set_cursor(settings.map_length / 2 + 1, settings.map_width - kFinalScoreStringLength / 2 - 1);
        std::cout << "Final score: " << death_score << std::endl;

        console.set_cursor(settings.map_length + 1, 1);
        return 0;
    }

    console.set_cursor(settings.map_length / 2, settings.map_width - kFinalScoreStringLength / 2 - 1);
    std::cout << "Final score: " << death_score << std::endl;

    console.set_cursor(settings.map_length + 1, 1);
    return 0;
}

void Game::print_control_error_screen() {
    ConsoleUI console;
    console.set_cursor(settings.map_width + 3, 1);
    std::cout << "Wrong key was pressed. Please, check controls settings" << std::endl;
    usleep(500000);
}

Game::~Game() {
    ConsoleUI::on_cursor();
}
