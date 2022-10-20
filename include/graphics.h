#pragma once

#include <iostream>
#include "cpp-terminal/base.hpp"

#include "settings.h"

const int SHADE_NUM = 4;
const int SHADE_DIFF = 20;

class Graphics {
// Bирутальный класс графики
public:
    virtual void print_empty_cell() = 0;
    virtual void print_snake_cell(int) = 0;
    virtual void print_snake_head_cell(int) = 0;
    virtual void print_wall_cell() = 0;
    virtual void print_teleport_cell() = 0;
    virtual void print_bonus_cell() = 0;
    virtual void print_antibonus_cell() = 0;
    virtual void print_speed_bonus_cell() = 0;
    virtual void print_speed_antibonus_cell() = 0;
};

class ColorGraphics : public Graphics {
// Bирутальный класс цветной графики
protected:
    explicit ColorGraphics(Settings);

    Term::RGB snake_color;
    Term::RGB empty_color;
    Term::RGB wall_color;
    Term::RGB teleport_color;
    Term::RGB bonus_color;
    Term::RGB antibonus_color;
    Term::RGB speed_bonus_color;
    Term::RGB speed_antibonus_color;
};

// Переопределения графики

class SymGraphics : public Graphics {
public:
    void print_empty_cell() override;
    void print_snake_cell(int) override;
    void print_snake_head_cell(int) override;
    void print_wall_cell() override;
    void print_teleport_cell() override;
    void print_bonus_cell() override;
    void print_antibonus_cell() override;
    void print_speed_bonus_cell() override;
    void print_speed_antibonus_cell() override;
};

class EscSymGraphics : public ColorGraphics {
public:
    explicit EscSymGraphics(Settings);
    void print_empty_cell() override;
    void print_snake_cell(int) override;
    void print_snake_head_cell(int) override;
    void print_wall_cell() override;
    void print_teleport_cell() override;
    void print_bonus_cell() override;
    void print_antibonus_cell() override;
    void print_speed_bonus_cell() override;
    void print_speed_antibonus_cell() override;
};

class EscGraphics : public ColorGraphics {
public:
    explicit EscGraphics(Settings);
    void print_empty_cell() override;
    void print_snake_cell(int) override;
    void print_snake_head_cell(int) override;
    void print_wall_cell() override;
    void print_teleport_cell() override;
    void print_bonus_cell() override;
    void print_antibonus_cell() override;
    void print_speed_bonus_cell() override;
    void print_speed_antibonus_cell() override;
};
