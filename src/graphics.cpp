#include "graphics.h"

ColorGraphics::ColorGraphics(Settings settings) : snake_color(settings.snake_color),
                                                  empty_color(settings.empty_color),
                                                  wall_color(settings.wall_color),
                                                  teleport_color(settings.teleport_color),
                                                  bonus_color(settings.bonus_color),
                                                  antibonus_color(settings.antibonus_color),
                                                  speed_bonus_color(settings.speed_bonus_color),
                                                  speed_antibonus_color(settings.speed_antibonus_color) {}

void SymGraphics::print_empty_cell() {
    std::cout << ' ';
    std::cout << ' ';
}

void SymGraphics::print_snake_cell(int snake_shade) {
    std::cout << 'o';
    std::cout << ' ';
}

void SymGraphics::print_snake_head_cell(int snake_shade) {
    std::cout << 'O';
    std::cout << ' ';
}

void SymGraphics::print_wall_cell() {
    std::cout << '*';
    std::cout << ' ';
}

void SymGraphics::print_teleport_cell() {
    std::cout << '*';
    std::cout << ' ';
}

void SymGraphics::print_bonus_cell() {
    std::cout << 'X';
    std::cout << ' ';
}

void SymGraphics::print_antibonus_cell() {
    std::cout << 'W';
    std::cout << ' ';
}

void SymGraphics::print_speed_bonus_cell() {
    std::cout << 'S';
    std::cout << ' ';
}

void SymGraphics::print_speed_antibonus_cell() {
    std::cout << 's';
    std::cout << ' ';
}

///

EscSymGraphics::EscSymGraphics(Settings settings) : ColorGraphics(settings) {}

void EscSymGraphics::print_empty_cell() {
    std::cout << Term::color_fg(empty_color) << ' ';
    std::cout << Term::color_fg(empty_color) << ' ';
}

void EscSymGraphics::print_snake_cell(int snake_shade) {
    Term::RGB color{snake_color.r, static_cast<uint8_t>(snake_color.g - SHADE_DIFF * snake_shade), snake_color.b};
    std::cout << Term::color_fg(color) << 'o';
    std::cout << Term::color_fg(empty_color) << ' ';
}

void EscSymGraphics::print_snake_head_cell(int snake_shade) {
    Term::RGB color{snake_color.r, static_cast<uint8_t>(snake_color.g - SHADE_DIFF * snake_shade), snake_color.b};
    std::cout << Term::color_fg(color) << 'O';
    std::cout << Term::color_fg(empty_color) << ' ';
}

void EscSymGraphics::print_wall_cell() {
    std::cout << Term::color_fg(wall_color) << '*';
    std::cout << Term::color_fg(empty_color) << ' ';
}

void EscSymGraphics::print_teleport_cell() {
    std::cout << Term::color_fg(teleport_color) << '#';
    std::cout << Term::color_fg(empty_color) << ' ';
}

void EscSymGraphics::print_bonus_cell() {
    std::cout << Term::color_fg(bonus_color) << 'X';
    std::cout << Term::color_fg(empty_color) << ' ';
}

void EscSymGraphics::print_antibonus_cell() {
    std::cout << Term::color_fg(antibonus_color) << 'W';
    std::cout << Term::color_fg(empty_color) << ' ';
}

void EscSymGraphics::print_speed_bonus_cell() {
    std::cout << Term::color_fg(speed_bonus_color) << 'S';
    std::cout << Term::color_fg(empty_color) << ' ';
}

void EscSymGraphics::print_speed_antibonus_cell() {
    std::cout << Term::color_fg(speed_antibonus_color) << 's';
    std::cout << Term::color_fg(empty_color) << ' ';
}


///
EscGraphics::EscGraphics(Settings settings) : ColorGraphics(settings) {}

void EscGraphics::print_empty_cell() {
    std::cout << Term::color_bg(empty_color) << ' ';
    std::cout << Term::color_bg(empty_color) << ' ';
}

void EscGraphics::print_snake_cell(int snake_shade) {
    int green_color = (snake_color.g < 99) ? snake_color.g: snake_color.g - SHADE_DIFF * snake_shade;
    Term::RGB color{snake_color.r, static_cast<uint8_t>(green_color), snake_color.b};
    std::cout << Term::color_bg(color) << ' ';
    std::cout << Term::color_bg(color) << ' ';
}

void EscGraphics::print_snake_head_cell(int snake_shade) {
    int green_color = (snake_color.g < 99) ? snake_color.g: snake_color.g - SHADE_DIFF * snake_shade;
    Term::RGB color{snake_color.r, static_cast<uint8_t>(green_color), snake_color.b};
    std::cout << Term::color_bg(color) << ' ';
    std::cout << Term::color_bg(color) << ' ';
}

void EscGraphics::print_wall_cell() {
    std::cout << Term::color_bg(wall_color) << ' ';
    std::cout << Term::color_bg(wall_color) << ' ';
}

void EscGraphics::print_teleport_cell() {
    std::cout << Term::color_bg(teleport_color) << ' ';
    std::cout << Term::color_bg(teleport_color) << ' ';
}

void EscGraphics::print_bonus_cell() {
    std::cout << Term::color_bg(bonus_color) << ' ';
    std::cout << Term::color_bg(bonus_color) << ' ';
}

void EscGraphics::print_antibonus_cell() {
    std::cout << Term::color_bg(antibonus_color) << ' ';
    std::cout << Term::color_bg(antibonus_color) << ' ';
}

void EscGraphics::print_speed_bonus_cell() {
    std::cout << Term::color_bg(speed_bonus_color) << ' ';
    std::cout << Term::color_bg(speed_bonus_color) << ' ';
}

void EscGraphics::print_speed_antibonus_cell() {
    std::cout << Term::color_bg(speed_antibonus_color) << ' ';
    std::cout << Term::color_bg(speed_antibonus_color) << ' ';
}
