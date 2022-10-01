#include "game.h"

Game::Game() : highest_score(0), death_score(0) {}

bool Game::start_level(unsigned level_number) {
    parser(settings);

    Snake snake(settings);
    KeyboardControl control(settings);
    ConsoleUI console;
    MapModel map_model(settings);
    MapView map_view(map_model, settings);

    bool is_exit = false;
    unsigned eaten_bonuses_number = 0;

    unsigned moves_number = 0;
    unsigned moves_number_after_bonus = 0;
    float speed_of_bonus = 1.0;

    console.set_cursor(0, 0);
    console.clear_display();

    map_model.put_snake(snake);
    map_model.generate_bonus(BONUS);
    if (settings.bonus_apples) {
        map_model.generate_bonus(ANTIBONUS);
        map_model.generate_bonus(SPEED_BONUS);
        map_model.generate_bonus(SPEED_ANTIBONUS);
    }
    map_view.print();

    while (!is_exit) {
        Direction last_dir = snake.get_direction();
        Direction new_dir = control.read_direction(last_dir);

        if (last_dir != new_dir && control.check_direction(last_dir, new_dir)) {
            snake.set_direction(new_dir);
        }

        Position next_cell = snake.get_next();
        switch (map_model.check_cell(next_cell.get_x(), next_cell.get_y())) {
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
        console.set_cursor(0, 0);
        console.clear_display();

        map_model.put_snake(snake);
        map_view.print();

        if (settings.score) {
            std::cout << "\033[" << map_model.get_length() - 4 << "CSCORE: " << snake.get_snake().size() << std::endl;
        }

        death_score = snake.get_snake().size();
        if (death_score > highest_score) {
            highest_score = death_score;
        }

        if (moves_number_after_bonus == MOVES_FOR_SPEED_BONUS) {
            speed_of_bonus = 1.0;
        }

        ++moves_number;
        ++moves_number_after_bonus;

        usleep(MOVE_PAUSE / snake.get_speed_coef() / speed_of_bonus / LEVEL_SPEED(level_number));

        if (eaten_bonuses_number == BONUSES_FOR_NEW_LEVEL) {
            return true;
        }
    }
    return false;
}

int Game::start_game(bool random_apples) {
    std::clock_t start_time = std::clock();

    bool is_exit = false;
    unsigned level_number = 0;

    while (!is_exit) {
        is_exit = !start_level(level_number);

        usleep(LEVEL_PAUSE);
    }

    random_apples ? srand(1) : srand(time(0));


    game_time = (std::clock() - start_time) / (double) CLOCKS_PER_SEC;

    return 0;
}

int Game::deathscreen() {
    usleep(3000);
    ConsoleUI console;
    console.set_cursor(0, 0);
    console.clear_display();
    std::cout << "Play time: " << game_time << " seconds" << std::endl;
    if (settings.bonus_apples) {
        std::cout << "Highest score : " << highest_score << std::endl;
    }
    std::cout << "Final score : " << death_score << std::endl;

    return 0;
}