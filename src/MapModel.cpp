#include <MapModel.h>

MapModel::MapModel(unsigned _width, unsigned _length) {
    width = _width;
    length = _length;
    field = new Cell* [width];
    for (int i = 0; i < width; i++)
        field[i] = new Cell[length];
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < length; j++) {
            field[i][j] = EMPTY;
            if (i == 0 || i == width - 1 || j == 0 || j == length - 1)
                field[i][j] = WALL;
        }
    }
}

// MapModel::~MapModel() {
//     for(int i = 0; i < width; i++) {
//         delete[] field[i];
//     }
//     delete[] field;
// }

unsigned MapModel::get_width() {
    return width;
}

unsigned MapModel::get_length() {
    return length;
}

Cell MapModel::get_cell(unsigned width, unsigned length) {
    return field[width][length];
}

void MapModel::clear_cell(unsigned x, unsigned y) {
    field[x][y] = EMPTY;
}

Cell MapModel::check_block(unsigned x, unsigned y) {
    return field[x][y];
}

void MapModel::put_snake(Snake s) {
    list <Position>::iterator it = s.snake.begin();
    while (it != s.snake.end()) {
        Position d = *it;
        field[d.get_x()][d.get_y()] = SNAKE;
        it++;
    }
}
