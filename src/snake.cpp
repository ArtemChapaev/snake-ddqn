#include "snake.h"

Position::Position(unsigned x, unsigned y) : x(x), y(y) {}

bool Position::operator==(Position other) {
    if (x == other.get_x() && y == other.get_y()) {
        return true;
    }
    return false;
}

unsigned Position::get_x() {
    return x;
}

unsigned Position::get_y() {
    return y;
}

Snake::Snake(Settings settings, unsigned length = kSnakeLength) : length(length), direction(right),
                                                                  speed_coef(settings.speed) {
    if (length >= settings.map_length - 2) {
        unsigned x = settings.map_length / 6;

        for (unsigned i = 0; i <= length / settings.map_width; ++i) {
            for (unsigned y = 1; y < settings.map_width - 1; ++y) {
                if (i % 2) {
                    snake.emplace_front(x + i, y);
                } else {
                    snake.emplace_front(x + i, settings.map_width - 1 - y);
                }
                if (i * (settings.map_width - 2) + y == length) {
                    return;
                }
            }
        }
    } else {
        unsigned y = settings.map_width * kStandartForY;
        unsigned x = 0;

        if (settings.map_length * kStandartForX >= length) {
            x = settings.map_length * kIndexForX + length;
        } else {
            x = length;
        }

        for (int i = 0; i < length; ++i) {
            snake.emplace_back(x, y);
            --x;
        }
    }
}


Position Snake::get_head() {
    return snake.front();
}

Position Snake::get_tail() {
    return snake.back();
}

std::list<Position> Snake::get_snake() {
    return snake;
}

Position Snake::get_next() {
    Position head = get_head();

    switch (direction) {
        case right: {
            return {head.get_x() + 1, head.get_y()};
        }
        case left : {
            return {head.get_x() - 1, head.get_y()};
        }
        case up: {
            return {head.get_x(), head.get_y() + 1};
        }
        default: {
            return {head.get_x(), head.get_y() - 1};
        }
    }
}

Keys Snake::get_direction() {
    return direction;
}

void Snake::set_direction(Keys dir) {
    direction = dir;
}

float Snake::get_speed_coef() {
    return speed_coef;
}

Position Snake::move_in_cell(Position pos_for_next) {
    for (auto &s: snake) {
        auto temp = s;
        s = pos_for_next;
        pos_for_next = temp;
    }
    return pos_for_next; // pos of tail
}

Position Snake::move() {
    return move_in_cell(get_next());
}

int Snake::increase_length(Position pos_for_tail) {
    snake.push_back(pos_for_tail);
    ++length;
    return 0;
}

Position Snake::decrease_length() {
    Position tail = snake.back();
    snake.pop_back();
    --length;
    return tail;
}

Position Snake::relocate_snake(Settings settings, MapModel map) {
    Position next_cell = get_next();
    unsigned x = 0;
    unsigned y = 0;
    if (next_cell.get_x() == 0) {
        x = settings.map_length - 2;
        y = next_cell.get_y();
        return move_in_cell({x, y});
    } else if (next_cell.get_x() == settings.map_length - 1) {
        return move_in_cell({1, next_cell.get_y()});
    } else if (next_cell.get_y() == 0) {
        return move_in_cell({next_cell.get_x(), settings.map_width - 2});
    } else if (next_cell.get_y() == settings.map_width - 1) {
        return move_in_cell({next_cell.get_x(), 1});
    } else {
        switch (get_direction()) {
            case up:
                return move_in_cell(
                        {settings.map_length - next_cell.get_x() - 1, settings.map_width - next_cell.get_y()});
            case down:
                return move_in_cell(
                        {settings.map_length - next_cell.get_x() - 1, settings.map_width - next_cell.get_y() - 2});
            case right:
                return move_in_cell(
                        {settings.map_length - next_cell.get_x(), settings.map_width - next_cell.get_y() - 1});
            case left:
                return move_in_cell(
                        {settings.map_length - next_cell.get_x() - 2, settings.map_width - next_cell.get_y() - 1});
        }
        return 0; // unreachable code
    }
}
