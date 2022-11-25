#include "mapModel.h"

MapModel::MapModel(Settings settings) : length(settings.map_length), width(settings.map_width) {
    field = new Cell *[width];

    Cell wall_type;
    settings.solid_wall ? wall_type = Cell::wall_c : wall_type = Cell::teleport_c;

    for (int i = 0; i < width; i++) {
        field[i] = new Cell[length];
        for (int j = 0; j < length; j++) {
            if (i == 0 || i == width - 1 || j == 0 || j == length - 1) {
                field[i][j] = wall_type;
            } else {
                field[i][j] = Cell::empty_c;
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

    field[it->get_y()][it->get_x()] = Cell::snake_head_c;
    ++it;

    while (it != snake.end()) {
        Position d = *it;
        field[d.get_y()][d.get_x()] = Cell::snake_c;
        ++it;
    }
}

void MapModel::generate_bonus(Cell bonus) {
    bool bonus_created = false;
    while (!bonus_created) {
        unsigned x = rand() % (length - 2) + 1; // to have fewer iterations of the loop
        unsigned y = rand() % (width - 2) + 1;
        if (check_cell(y, x) == empty_c && validate_teleports(y, x)) {
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
    field[pos.get_y()][pos.get_x()] = Cell::empty_c;
}

Cell MapModel::check_cell(unsigned y, unsigned x) {
    return field[y][x];
}

void MapModel::set_cell(unsigned y, unsigned x, Cell cell) {
    field[y][x] = cell;
}

bool MapModel::validate_teleports(unsigned y, unsigned x) {
    if (field[y + 1][x - 1] == teleport_c || field[y + 1][x] == teleport_c || field[y + 1][x + 1] == teleport_c ||
        field[y][x - 1] == teleport_c || field[y][x + 1] == teleport_c ||
        field[y - 1][x - 1] == teleport_c || field[y - 1][x] == teleport_c || field[y - 1][x + 1] == teleport_c) {
        return false;
    }
    return true;
}

MapModel read_map_from_file(Settings settings) {
    MapModel map(settings);
    std::ifstream file("map.txt");
    char sym;

    for (unsigned j = map.get_width() - 2; j >= 1; j--) {
        for (unsigned i = 1; i < map.get_length() - 1; i++) {

            file >> sym;
            if (sym == 'W') {
                map.set_cell(j, i, wall_c);
            } else if (sym == 'T') {
                map.set_cell(j, i, teleport_c);
            }
        }
        std::string end_of_line;
        getline(file, end_of_line);
    }

    file.close();
    return map;
}

void write_map_to_file(MapModel &map) {
    std::ofstream file("map.txt");
    for (unsigned j = map.get_width() - 2; j >= 1; j--) {
        for (unsigned i = 1; i < map.get_length() - 1; i++) {

            Cell cell = map.check_cell(j, i);
            if (cell == wall_c) {
                file << 'W';
            } else if (cell == teleport_c) {
                file << 'T';
            } else {
                file << 'E';
            }
        }
        file << '\n';
    }
    file.close();
}
