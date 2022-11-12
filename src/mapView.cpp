#include "mapView.h"

MapView::MapView(MapModel &map, Settings settings) : map(map), graphics(NULL) {
    switch (settings.view_mode) {
        case 0:
            graphics = new SymGraphics;
            break;
        case 1:
            graphics = new EscSymGraphics(settings);
            break;
        case 2:
            graphics = new EscGraphics(settings);
            break;
    }
}

void MapView::print_walls() {
    for (int j = 1; j <= map.get_width(); j++) {
        for (int i = 1; i <= map.get_length(); i++) {
            if (j == 1 || j == map.get_width() || i == 1 || i == map.get_length()) {
                std::cout << "\033[" << i << ";" << j * 2 << "H";
                graphics->print_wall_cell();
            }
        }
    }
    std::cout << "\033[0m" << std::flush;
}


void MapView::print() {
    int snake_shade = 0;
    for (int j = map.get_width() - 1; j >= 0; j--) {
        for (int i = 0; i < map.get_length(); i++) {
            switch (map.check_cell(j, i)) {
                case empty_c:
                    graphics->print_empty_cell();
                    break;
                case snake_c:
                    graphics->print_snake_cell(snake_shade);
                    snake_shade = (snake_shade + 1) % SHADE_NUM;
                    break;
                case snake_head_c:
                    graphics->print_snake_head_cell(snake_shade);
                    snake_shade = (snake_shade + 1) % SHADE_NUM;
                    break;
                case wall_c:
                    graphics->print_wall_cell();
                    break;
                case teleport_c:
                    graphics->print_teleport_cell();
                    break;
                case bonus_c:
                    graphics->print_bonus_cell();
                    break;
                case antibonus_c:
                    graphics->print_antibonus_cell();
                    break;
                case speed_bonus_c:
                    graphics->print_speed_bonus_cell();
                    break;
                case speed_antibonus_c:
                    graphics->print_speed_antibonus_cell();
                    break;
            }
        }
        std::cout << std::endl;
    }
    std::cout << "\033[0m" << std::flush;
}

MapView::~MapView() {
    delete graphics;
}
