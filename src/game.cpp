#include "game.h"

Game::Game(std::string file) : filename(file), highest_score(0), death_score(0) {}

bool Game::start_level(unsigned level_number) {
    parser(settings, filename);

    unsigned snake_length = SNAKE_LENGTH;
    if (!settings.reset_length) {
        snake_length = death_score + SNAKE_LENGTH; // bcs for last level: death_score = snake.size() - SNAKE_LENGTH
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

    map_model.generate_bonus(BONUS);
    if (settings.bonus_apples) {
        map_model.generate_bonus(ANTIBONUS);
        map_model.generate_bonus(SPEED_BONUS);
        map_model.generate_bonus(SPEED_ANTIBONUS);
    }

    console.set_cursor(1, 1);
    console.clear_full_display();

    map_model.put_snake(snake);
    map_view.print();

    while (!is_exit) {
        Keys last_dir = snake.get_direction();
        Keys new_key = control.read_key(last_dir);
        if (new_key == Keys::interruption) {
            usleep(GAME_PAUSE);
            continue;
        }

        if (last_dir != new_key && control.check_direction(last_dir, new_key)) {
            snake.set_direction(new_key);
        }

        Position next_cell = snake.get_next();
        switch (map_model.check_cell(next_cell.get_y(), next_cell.get_x())) {
            case BONUS: {
                Position last_tail = snake.move();
                snake.increase_length(last_tail);
                map_model.generate_bonus(BONUS);

                ++eaten_bonuses_number;
                break;
            }
            case ANTIBONUS: {
                Position last_tail = snake.move();
                map_model.clear_cell(last_tail);

                last_tail = snake.decrease_length();
                map_model.clear_cell(last_tail);
                map_model.generate_bonus(ANTIBONUS);

                console.clear_game_field(settings);

                if (snake.get_snake().size() == 0) {
                    is_exit = true;
                } else {
                    ++eaten_bonuses_number; // при одновременном выполнении двух событий, уровень не будет пройденным
                }
                break;
            }
            case SPEED_BONUS: {
                Position last_tail = snake.move();
                map_model.clear_cell(last_tail);
                map_model.generate_bonus(SPEED_BONUS);

                moves_number_after_bonus = 0;
                speed_of_bonus = BONUS_SPEED_FOR_SNAKE;

                ++eaten_bonuses_number;
                break;
            }
            case SPEED_ANTIBONUS: {
                Position last_tail = snake.move();
                map_model.clear_cell(last_tail);
                map_model.generate_bonus(SPEED_ANTIBONUS);

                moves_number_after_bonus = 0;
                speed_of_bonus = 1.0 / BONUS_SPEED_FOR_SNAKE;

                ++eaten_bonuses_number;
                break;
            }
            case SNAKE: {
                if (snake.get_tail() == next_cell) {
                    snake.move(); // без clear_cell, тк все равно будет в той клетке голова
                    break;
                }
                // если не идет по if, то проваливается в следующий case
            }
            case WALL: {
                is_exit = true;
                break;
            }
            case TELEPORT: {
                Position last_tail = snake.relocate_snake(settings);
                map_model.clear_cell(last_tail);
                break;
            }
            case EMPTY: {
                Position last_tail = snake.move();
                map_model.clear_cell(last_tail);
                break;
            }
        }

        console.set_cursor(1, 1);

        map_model.put_snake(snake);
        map_view.print();

        death_score = (int) (snake.get_snake().size() - SNAKE_LENGTH) > 0 ? snake.get_snake().size() - SNAKE_LENGTH : 0;
        highest_score = death_score > highest_score ? death_score : highest_score;

        if (settings.score) {
            unsigned score = death_score;
            std::cout << "\033[" << map_model.get_length() - 5 << "CSCORE: " << score << std::endl; // what esc-seq???
        }

        if (moves_number_after_bonus == MOVES_FOR_SPEED_BONUS) {
            speed_of_bonus = 1.0;
        }

        ++moves_number;
        ++moves_number_after_bonus;

        usleep(MOVE_PAUSE / snake.get_speed_coef() / speed_of_bonus / LEVEL_SPEED(level_number));
        if (eaten_bonuses_number == BONUSES_FOR_NEW_LEVEL) {
            console.clear_full_display();
            // usleep(100);
            console.set_cursor(settings.map_length - WIN_STRING.size() / 2, settings.map_width / 2); // don't work
            // usleep(100);
            std::cout << WIN_STRING;
            // usleep(GAME_PAUSE);
            return true;
        }
    }
    return false;
}

int Game::start_game(bool random_apples) {
    auto start_time = std::chrono::high_resolution_clock::now();
    bool is_exit = false;
    unsigned level_number = 0;

    random_apples ? srand(time(0)) : srand(1);

    while (!is_exit) {
        is_exit = !start_level(level_number);
        usleep(LEVEL_PAUSE);
    }

    std::chrono::duration<float> duration = std::chrono::high_resolution_clock::now() - start_time;
    game_time = duration.count();
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