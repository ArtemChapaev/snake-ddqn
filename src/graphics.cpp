#include "graphics.h"

void SymGraphics::print_empty_cell() {
    std::cout << ' ';
    std::cout << ' ';
}

void SymGraphics::print_snake_cell() {
    std::cout << 'o';
    std::cout << ' ';
}

void SymGraphics::print_snake_head_cell() {
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

void EscSymGraphics::print_empty_cell() {
    std::cout << ' ';
    std::cout << ' ';
}

void EscSymGraphics::print_snake_cell() {
    std::cout << "\033[1;32mo\033[0m";
    std::cout << "\033[m \033[0m";

}

void EscSymGraphics::print_snake_head_cell() {
    std::cout << "\033[1;32mO\033[0m";
    std::cout << "\033[2m \033[0m";
}

void EscSymGraphics::print_wall_cell() {
    std::cout << "\033[36m*\033[0m";
    std::cout << "\033[m \033[0m";
}

void EscSymGraphics::print_teleport_cell() {
    std::cout << "\033[37;40m*\033[0m";
    std::cout << "\033[m \033[0m";
}

void EscSymGraphics::print_bonus_cell() {
    std::cout << "\033[1;31mX\033[0m";
    std::cout << "\033[m \033[0m";
}

void EscSymGraphics::print_antibonus_cell() {
    std::cout << "\033[1;33mW\033[0m";
    std::cout << "\033[m \033[0m";
}

void EscSymGraphics::print_speed_bonus_cell() {
    std::cout << "\033[1;34mS\033[0m";
    std::cout << "\033[m \033[0m";
}

void EscSymGraphics::print_speed_antibonus_cell() {
    std::cout << "\033[1;33ms\033[0m";
    std::cout << "\033[m \033[0m";
}


///

void EscGraphics::print_empty_cell() {
    std::cout << "\033[47m \033[0m";
    std::cout << "\033[47m \033[0m";
}

void EscGraphics::print_snake_cell() {
    std::cout << "\033[42m \033[0m";
    std::cout << "\033[42m \033[0m";
}

void EscGraphics::print_snake_head_cell() {
    std::cout << "\033[42m \033[0m";
    std::cout << "\033[42m \033[0m";
}

void EscGraphics::print_wall_cell() {
    std::cout << "\033[40m \033[0m";
    std::cout << "\033[40m \033[0m";
}

void EscGraphics::print_teleport_cell() {
    std::cout << "\033[40m \033[0m";
    std::cout << "\033[40m \033[0m";
}

void EscGraphics::print_bonus_cell() {
    std::cout << "\033[41m \033[0m";
    std::cout << "\033[41m \033[0m";
}

void EscGraphics::print_antibonus_cell() {
    std::cout << "\033[43m \033[0m";
    std::cout << "\033[43m \033[0m";
}

void EscGraphics::print_speed_bonus_cell() {
    std::cout << "\033[44m \033[0m";
    std::cout << "\033[44m \033[0m";
}

void EscGraphics::print_speed_antibonus_cell() {
    std::cout << "\033[43m \033[0m";
    std::cout << "\033[43m \033[0m";
}
