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
        unsigned x = rand() % (length - 2) + 1;  // to have fewer iterations of the loop
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
    if (field[y + 1][x - 1] == teleport_c || field[y + 1][x] == teleport_c ||
        field[y - 1][x - 1] == teleport_c || field[y - 1][x] == teleport_c || field[y][x + 1] == teleport_c ||
        field[y][x - 1] == teleport_c || field[y + 1][x + 1] == teleport_c ||
        field[y - 1][x + 1] == teleport_c) {
        return false;
    }
    return true;
}

MapModel read_map_from_file(Settings settings) {
    MapModel map(settings);
    std::ifstream file(kMapFile);
    if (!file.is_open()) {
        // use default map
        write_map_to_file(map);
        return map;
    }

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
    std::ofstream file(kMapFile);
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

std::vector<double> get_state(MapModel &map, Snake s) {
    unsigned x_head = s.get_head().get_x();
    unsigned y_head = s.get_head().get_y();

    // NEED CONSTANT-VALUE
    std::vector<double> state(32);

    // properties that related with walls
    {
        state[0] = 1.0 / (map.get_width() - y_head);
        state[1] = 1.0 / (map.get_width() - y_head + map.get_length() - x_head);
        state[2] = 1.0 / (map.get_length() - x_head);
        state[3] = 1.0 / (y_head + map.get_length() - x_head);
        state[4] = 1.0 / y_head;
        state[5] = 1.0 / (y_head + x_head);
        state[6] = 1.0 / x_head;
        state[7] = 1.0 / (map.get_width() - y_head + x_head);
    }

    // properties that related with snake body
    {
        auto snake = s.get_snake();
        auto s_body = snake.begin();
        // we don't check head, so ++s_body;
        ++s_body;

        for (; s_body != snake.end(); ++s_body) {
            if (s_body->get_x() == x_head) {
                if (s_body->get_y() > y_head) {
                    // above head
                    double temp = 1.0 / (s_body->get_y() - y_head);
                    state[8] = std::max(temp, state[8]);
                } else {
                    // under head
                    double temp = 1.0 / (y_head - s_body->get_y());
                    state[12] = std::max(temp, state[12]);
                }
            } else if (s_body->get_y() == y_head) {
                if (s_body->get_x() > x_head) {
                    // right head
                    double temp = 1.0 / (s_body->get_x() - x_head);
                    state[10] = std::max(temp, state[10]);
                } else {
                    // left head
                    double temp = 1.0 / (x_head - s_body->get_x());
                    state[14] = std::max(temp, state[14]);
                }
            } else if (s_body->get_y() - s_body->get_x() == y_head - x_head) {
                if (s_body->get_y() > y_head) {
                    // in main diagonal above head
                    double temp = 0.5 / (s_body->get_y() - y_head);
                    state[15] = std::max(temp, state[15]);
                } else {
                    // in main diagonal under head
                    double temp = 0.5 / (y_head - s_body->get_y());
                    state[11] = std::max(temp, state[11]);
                }
            } else if (s_body->get_y() + s_body->get_x() == y_head + x_head) {
                if (s_body->get_y() > y_head) {
                    // in side diagonal above head
                    double temp = 0.5 / (s_body->get_y() - y_head);
                    state[9] = std::max(temp, state[9]);
                } else {
                    // in side diagonal under head
                    double temp = 0.5 / (y_head - s_body->get_y());
                    state[13] = std::max(temp, state[13]);
                }
            }
        }
    }

    // properties that related with bonus
    {
        unsigned x_bonus = 0;
        unsigned y_bonus = 0;

        for (unsigned j = map.get_width() - 2; j >= 1; j--) {
            for (unsigned i = 1; i < map.get_length() - 1; i++) {
                Cell cell_type = map.check_cell(j, i);
                if (cell_type == Cell::bonus_c) {
                    x_bonus = i;
                    y_bonus = j;
                }
            }
        }

        if (x_bonus == x_head) {
            if (y_bonus > y_head) {
                // above head
                double temp = 1.0 / (y_bonus - y_head);
                state[16] = std::max(temp, state[16]);
            } else {
                // under head
                double temp = 1.0 / (y_head - y_bonus);
                state[20] = std::max(temp, state[20]);
            }
        } else if (y_bonus == y_head) {
            if (x_bonus > x_head) {
                // right head
                double temp = 1.0 / (x_bonus - x_head);
                state[18] = std::max(temp, state[18]);
            } else {
                // left head
                double temp = 1.0 / (x_head - y_bonus);
                state[22] = std::max(temp, state[22]);
            }
        } else if (y_bonus - x_bonus == y_head - x_head) {
            if (y_bonus > y_head) {
                // in main diagonal above head
                double temp = 0.5 / (y_bonus - y_head);
                state[23] = std::max(temp, state[23]);
            } else {
                // in main diagonal under head
                double temp = 0.5 / (y_head - y_bonus);
                state[19] = std::max(temp, state[19]);
            }
        } else if (y_bonus + x_bonus == y_head + x_head) {
            if (y_bonus > y_head) {
                // in side diagonal above head
                double temp = 0.5 / (y_bonus - y_head);
                state[17] = std::max(temp, state[17]);
            } else {
                // in side diagonal under head
                double temp = 0.5 / (y_head - y_bonus);
                state[21] = std::max(temp, state[21]);
            }
        }
    }

    // properties that related with direction of head and s
    {
        switch (s.get_direction()) {
            case Keys::up: {
                state[24] = 1.0;
                break;
            }
            case Keys::right: {
                state[25] = 1.0;
                break;
            }
            case Keys::down: {
                state[26] = 1.0;
                break;
            }
                // Keys::left
            default: {
                state[27] = 1.0;
                break;
            }
        }

        Position second_body_cell = *std::next(s.get_snake().begin());

        if (second_body_cell.get_x() == x_head) {
            if (second_body_cell.get_y() > y_head) {
                // above head
                state[28] = 1.0;
            } else {
                // under head
                state[30] = 1.0;
            }
        } else {
            if (second_body_cell.get_x() > x_head) {
                // right head
                state[29] = 1.0;
            } else {
                // left head
                state[31] = 1.0;
            }
        }
    }

    return state;
}
