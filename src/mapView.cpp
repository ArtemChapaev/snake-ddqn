#include "mapView.h"

MapView::MapView(MapModel &map, Settings settings) : map(map), graphics(NULL) {
	switch (settings.view_mode) {
        case 0:
            graphics = new SymGraphics;
            break;
        case 1:
            graphics = new EscSymGraphics;
            break;
        case 2:
            graphics = new EscGraphics;
            break;
    }
}

void MapView::deathscreen() {
    
}

void MapView::print() {
    for (int j = map.get_width() - 1; j >= 0; j--) {
        for (int i = 0; i < map.get_length(); i++) {
            switch (map.check_cell(i, j)) {
                case EMPTY:
                    graphics->print_empty_cell();
                    break;
                case SNAKE:
                    graphics->print_snake_cell();
                    break;
                case SNAKE_HEAD:
                    graphics->print_snake_head_cell();
                    break;
                case WALL:
                    graphics->print_wall_cell();
                    break;
                case TELEPORT:
                    graphics->print_teleport();
                    break;
                case FRUIT:
                    graphics->print_fruit_cell();
                    break;
                case ANTIFRUIT:
                    graphics->print_antifruit_cell();
                    break;
            }
        }
        std::cout << std::endl;
    }
}

MapView::~MapView() {
    delete graphics;
}
