#include <iostream>

#include "mapView.h"

MapView::MapView(MapModel map) : map(map), graphics(new SymGraphics) {}

void MapView::print() {
    for (int j = map.get_width(); j >= 0 ; j--) {
        for (int i = 0; i < map.get_length(); i++) {
            switch (map.check_cell(i, j)) {
                case EMPTY:
                    graphics->print_empty_cell();
                    break;
                case SNAKE:
                    graphics->print_snake_cell();
                    break;
                case WALL:
                    graphics->print_wall_cell();
                    break;
                case FRUIT:
                    graphics->print_fruit_cell();
                    break;
            }
        }
        std::cout << std::endl;
    }
}

MapView::~MapView() {
    delete graphics;
}

void SymGraphics::print_empty_cell() {
    std::cout << ' ';
}

void SymGraphics::print_snake_cell() {
    std::cout << 'O';
}

void SymGraphics::print_wall_cell() {
    std::cout << '*';
}

void SymGraphics::print_fruit_cell() {
    std::cout << 'X';
}
