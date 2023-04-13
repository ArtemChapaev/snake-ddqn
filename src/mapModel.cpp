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

State get_state(MapModel &map, Snake s) {
    unsigned x_head = s.get_head().get_x();
    unsigned y_head = s.get_head().get_y();

    State state;

    // properties that related with bonus
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
            state.dist_snake_up = std::max(temp, state.dist_snake_up);
        } else {
            // under head
            double temp = 1.0 / (y_head - y_bonus);
            state.dist_snake_down = std::max(temp, state.dist_snake_down);
        }
    } else if (y_bonus == y_head) {
        if (x_bonus > x_head) {
            // right head
            double temp = 1.0 / (x_bonus - x_head);
            state.dist_snake_right = std::max(temp, state.dist_snake_right);
        } else {
            // left head
            double temp = 1.0 / (x_head - y_bonus);
            state.dist_snake_left = std::max(temp, state.dist_snake_left);
        }
    } else if (y_bonus - x_bonus == y_head - x_head) {
        if (y_bonus > y_head) {
            // in left above head
            double temp = 0.5 / (y_bonus - y_head);
            state.dist_snake_up_left = std::max(temp, state.dist_snake_up_left);
        } else {
            // in right under head
            double temp = 0.5 / (y_head - y_bonus);
            state.dist_snake_down_right = std::max(temp, state.dist_snake_down_right);
        }
    } else if (y_bonus + x_bonus == y_head + x_head) {
        if (y_bonus > y_head) {
            // in right above head
            double temp = 0.5 / (y_bonus - y_head);
            state.dist_snake_up_right = std::max(temp, state.dist_snake_up_right);
        } else {
            // in left under head
            double temp = 0.5 / (y_head - y_bonus);
            state.dist_snake_down_left = std::max(temp, state.dist_snake_down_left);
        }
    }

    // properties that related with snake body
    auto snake = s.get_snake();
    auto s_body = snake.begin();
    // we don't check head, so ++s_body;
    ++s_body;

    for (; s_body != snake.end(); ++s_body) {
        if (s_body->get_x() == x_head) {
            if (s_body->get_y() > y_head) {
                // above head
                double temp = 1.0 / (s_body->get_y() - y_head);
                state.dist_snake_up = std::max(temp, state.dist_snake_up);
            } else {
                // under head
                double temp = 1.0 / (y_head - s_body->get_y());
                state.dist_snake_down = std::max(temp, state.dist_snake_down);
            }
        } else if (s_body->get_y() == y_head) {
            if (s_body->get_x() > x_head) {
                // right head
                double temp = 1.0 / (s_body->get_x() - x_head);
                state.dist_snake_right = std::max(temp, state.dist_snake_right);
            } else {
                // left head
                double temp = 1.0 / (x_head - s_body->get_x());
                state.dist_snake_left = std::max(temp, state.dist_snake_left);
            }
        } else if (s_body->get_y() - s_body->get_x() == y_head - x_head) {
            if (s_body->get_y() > y_head) {
                // in left above head
                double temp = 0.5 / (s_body->get_y() - y_head);
                state.dist_snake_up_left = std::max(temp, state.dist_snake_up_left);
            } else {
                // in right under head
                double temp = 0.5 / (y_head - s_body->get_y());
                state.dist_snake_down_right = std::max(temp, state.dist_snake_down_right);
            }
        } else if (s_body->get_y() + s_body->get_x() == y_head + x_head) {
            if (s_body->get_y() > y_head) {
                // in right above head
                double temp = 0.5 / (s_body->get_y() - y_head);
                state.dist_snake_up_right = std::max(temp, state.dist_snake_up_right);
            } else {
                // in left under head
                double temp = 0.5 / (y_head - s_body->get_y());
                state.dist_snake_down_left = std::max(temp, state.dist_snake_down_left);
            }
        }
    }

    // properties that related with walls
    state.dist_wall_up = 1.0 / (map.get_width() - y_head);
    state.dist_wall_up_right = 1.0 / (map.get_width() - y_head + map.get_length() - x_head);
    state.dist_wall_right = 1.0 / (map.get_length() - x_head);
    state.dist_wall_down_right = 1.0 / (y_head + map.get_length() - x_head);
    state.dist_wall_down = 1.0 / y_head;
    state.dist_wall_down_left = 1.0 / (y_head + x_head);
    state.dist_wall_left = 1.0 / x_head;
    state.dist_wall_up_left = 1.0 / (map.get_width() - y_head + x_head);

    // properties that related with direction of head
    switch (s.get_direction()) {
        case Keys::up: {
            state.head_direction_up = 1.0;
            break;
        }
        case Keys::right: {
            state.head_direction_right = 1.0;
            break;
        }
        case Keys::down: {
            state.head_direction_down = 1.0;
            break;
        }
            // Keys::left
        default: {
            state.head_direction_left = 1.0;
            break;
        }
    }

    // properties that related with direction of snake body
    Position second_body_cell = *std::next(s.get_snake().begin());

    if (second_body_cell.get_x() == x_head) {
        if (second_body_cell.get_y() > y_head) {
            // above head
            state.snake_direction_up = 1.0;
        } else {
            // under head
            state.snake_direction_down = 1.0;
        }
    } else {
        if (second_body_cell.get_x() > x_head) {
            // right head
            state.snake_direction_right = 1.0;
        } else {
            // left head
            state.snake_direction_left = 1.0;
        }
    }

    return state;
}

std::vector<double> state_struct_to_vector(const State &state) {
    std::vector<double> result(32);

    result[0] = state.dist_bonus_up;
    result[1] = state.dist_bonus_up_right;
    result[2] = state.dist_bonus_right;
    result[3] = state.dist_bonus_down_right;
    result[4] = state.dist_bonus_down;
    result[5] = state.dist_bonus_down_left;
    result[6] = state.dist_bonus_left;
    result[7] = state.dist_bonus_up_left;
    result[8] = state.dist_wall_up;
    result[9] = state.dist_wall_up_right;
    result[10] = state.dist_wall_right;
    result[11] = state.dist_wall_down_right;
    result[12] = state.dist_wall_down;
    result[13] = state.dist_wall_down_left;
    result[14] = state.dist_wall_left;
    result[15] = state.dist_wall_up_left;
    result[16] = state.dist_snake_up;
    result[17] = state.dist_snake_up_right;
    result[18] = state.dist_snake_right;
    result[19] = state.dist_snake_down_right;
    result[20] = state.dist_snake_down;
    result[21] = state.dist_snake_down_left;
    result[22] = state.dist_snake_left;
    result[23] = state.dist_snake_up_left;
    result[24] = state.head_direction_up;
    result[25] = state.head_direction_right;
    result[26] = state.head_direction_down;
    result[27] = state.head_direction_left;
    result[28] = state.snake_direction_up;
    result[29] = state.snake_direction_right;
    result[30] = state.snake_direction_down;
    result[31] = state.snake_direction_left;
    return result;
}
