#include <iostream>

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

void SymGraphics::print_fruit_cell() {
    std::cout << 'X';
    std::cout << ' ';
}

void SymGraphics::print_teleport() {
    std::cout << '*';
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

void EscSymGraphics::print_fruit_cell() {
    std::cout << "\033[1;31mX\033[0m";
    std::cout << "\033[m \033[0m";
}

void EscSymGraphics::print_teleport() {
    std::cout << "\033[37;40m*\033[0m";
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

void EscGraphics::print_fruit_cell() {
    std::cout << "\033[41m \033[0m";
    std::cout << "\033[41m \033[0m";
}

void EscGraphics::print_teleport() {
    std::cout << "\033[40m \033[0m";
    std::cout << "\033[40m \033[0m";
}