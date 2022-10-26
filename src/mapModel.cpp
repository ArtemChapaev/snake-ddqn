#include "mapModel.h"

MapModel::MapModel(Settings settings) : length(settings.map_length), width(settings.map_width) {
    field = new Cell *[width];

    Cell wall_type;
    settings.solid_wall ? wall_type = Cell::wall : wall_type = Cell::teleport;

    for (int i = 0; i < width; i++) {
        field[i] = new Cell[length];
        for (int j = 0; j < length; j++) {
            if (i == 0 || i == width - 1 || j == 0 || j == length - 1) {
                field[i][j] = wall_type;
            } else {
                field[i][j] = Cell::empty;
            }
        }
    }
}

MapModel::~MapModel() {
    for (int i = 0; i < width; i++) {
        delete[] field[i];
    }
    delete[] field;
}

void MapModel::put_snake(Snake s) {
    auto snake = s.get_snake();
    auto it = snake.begin();

    field[it->get_y()][it->get_x()] = Cell::snake_head;
    ++it;

    while (it != snake.end()) {
        Position d = *it;
        field[d.get_y()][d.get_x()] = Cell::snake;
        ++it;
    }
}

void MapModel::generate_bonus(Cell bonus) {
    bool bonus_created = false;
    while (!bonus_created) {
        unsigned x = rand() % (length - 2) + 1; // to have fewer iterations of the loop
        unsigned y = rand() % (width - 2) + 1;
        if (check_cell(y, x) == empty) {
            field[y][x] = bonus;
            bonus_created = true;
        }
    }
}

unsigned MapModel::get_width() {
    return width;
}

unsigned MapModel::get_length() {
    return length;
}

void MapModel::clear_cell(Position pos) {
    field[pos.get_y()][pos.get_x()] = Cell::empty;
}

Cell MapModel::check_cell(unsigned y, unsigned x) {
    return field[y][x];
}
