#include <cstdlib>
#include <ctime>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#include "consoleUI.h"
#include "control.h"
#include "game.h"
#include "keyboardControl.h"
#include "mapModel.h"
#include "mapView.h"
#include "settings.cpp"
#include "snake.h"

Game::Game(Settings settings) : settings(settings) {}

int Game::start_game(bool random_apples) {
    random_apples ? srand(1) : srand(time(0));
    
    Snake snake(settings);
    KeyboardControl control('w', 'a', 's', 'd');
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

        usleep(SNAKE_SPEED / snake.get_speed_coef());
    }
    return 0;
}
