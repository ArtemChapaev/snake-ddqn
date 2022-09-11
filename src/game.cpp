#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#include "consoleUI.h"
#include "control.h"
#include "game.h"
#include "mapModel.h"
#include "mapView.h"
#include "snake.h"

Game::Game(Settings settings): settings(settings) {}

int Game::start_game() {
    Snake snake(settings.map_length, settings.map_width);
    Control control('w', 'd', 's', 'a');
    ConsoleUI console;
    MapModel map_model(settings.map_length, settings.map_width);
    MapView map_view(map_model);

    bool is_exit = false;

    console.clear_display();
    console.set_cursor(0, 0);

    map_model.put_snake(snake);
    map_model.generate_fruit();
    map_view.print();

    int flags = fcntl(0, F_GETFL);
    control.enable_nonblock_input(flags);

    struct termios savetty;
    control.enable_noncanonical_input(savetty);

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
                map_model.generate_fruit();
                break;
            }
            case SNAKE: {
                if (snake.get_tail() == next_cell) {
                    snake.move(); // без clear_cell, тк все равно будет в той клетке голова
                    break;
                }
            }
            case WALL: {
                is_exit = true;
                break;
            }
            case EMPTY: {
                Position last_tail = snake.move();
                map_model.clear_cell(last_tail.get_x(), last_tail.get_y());
                break;
            }
        }

        usleep(SNAKE_SPEED / snake.get_speed_coef());

        console.clear_display();
        console.set_cursor(0, 0);

        map_model.put_snake(snake);
        map_view.print();
    }

    control.disable_nonblock_input(flags);
    control.disable_noncanonical_input(savetty);
    return 0;
}
