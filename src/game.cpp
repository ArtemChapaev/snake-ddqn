#include "game.h"

Game::Game(Settings settings) : settings(settings), highest_score(0), death_score(0) {}

int Game::start_game(bool random_apples) {
    std::clock_t start_time = std::clock();

    random_apples ? srand(1) : srand(time(0));
    parser(settings);

    Snake snake(settings);
    KeyboardControl control(settings.key_up, settings.key_left, settings.key_down, settings.key_right);
    ConsoleUI console;
    MapModel map_model(settings);
    MapView map_view(map_model, settings);

    bool is_exit = false;

    console.set_cursor(0, 0);
    console.clear_display();

    map_model.put_snake(snake);
    map_model.generate_fruit(FRUIT);
    if (settings.bonus_apples == true) {
        map_model.generate_fruit(ANTIFRUIT);
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
            case FRUIT: {
                Position last_tail = snake.move();
                snake.increase_length(last_tail);
                map_model.generate_fruit(FRUIT);
                break;
            }
            case ANTIFRUIT: {
                Position last_tail = snake.move();
                map_model.clear_cell(last_tail);

                last_tail = snake.decrease_length();
                map_model.clear_cell(last_tail);
                map_model.generate_fruit(ANTIFRUIT);

                if (snake.get_snake().size() == 0) {
                    is_exit = true;
                }
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

        if(settings.score) {
            std::cout << "\033[" << map_model.get_length() - 4 << "CSCORE: " << snake.get_snake().size() << std::endl;
        }

        death_score = snake.get_snake().size();
        if (death_score > highest_score) {
            highest_score = death_score;
        }

        usleep(SNAKE_SPEED / snake.get_speed_coef());
    }

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
}