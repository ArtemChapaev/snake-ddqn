#include "mapModel.h"

MapModel::MapModel(Settings settings) : length(settings.map_length), width(settings.map_width) {
    field = new Cell *[width];

    Cell wall_type;
    settings.solid_wall ? wall_type = WALL : wall_type = TELEPORT;

    for (int i = 0; i < width; i++) {
        field[i] = new Cell[length];
        for (int j = 0; j < length; j++) {
            if (i == 0 || i == width - 1 || j == 0 || j == length - 1) {
                field[i][j] = wall_type;
            } else {
                field[i][j] = EMPTY;
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

    field[it->get_x()][it->get_y()] = SNAKE_HEAD;
    ++it;

    while (it != snake.end()) {
        Position d = *it;
        field[d.get_x()][d.get_y()] = SNAKE;
        ++it;
    }
}

void MapModel::generate_fruit(Cell bonus) {
    bool fruit_created = false;
    while (!fruit_created) {
        unsigned x = rand() % (length - 2) + 1; // чтобы было меньше итераций цикла, из-за отсутствия WALL
        unsigned y = rand() % (width - 2) + 1;
        if (check_cell(x, y) == EMPTY) {
            field[x][y] = bonus;
            fruit_created = true;
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
    field[pos.get_x()][pos.get_y()] = EMPTY;
}

Cell MapModel::check_cell(unsigned x, unsigned y) {
    return field[x][y];
}
