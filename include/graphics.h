#pragma once

#include <iostream>

#include "cpp-terminal/base.hpp"
#include "settings.h"

class Graphics {
    // Abstract class for graphics
   public:
    virtual void print_empty_cell() = 0;
    virtual void print_snake_cell() = 0;
    virtual void print_snake_head_cell() = 0;
    virtual void print_wall_cell() = 0;
    virtual void print_teleport_cell() = 0;
    virtual void print_bonus_cell() = 0;
    virtual void print_antibonus_cell() = 0;
    virtual void print_speed_bonus_cell() = 0;
    virtual void print_speed_antibonus_cell() = 0;
    virtual ~Graphics() = default;
};

class ColorGraphics : public Graphics {
    // Abstract class for colored graphics
   protected:
    explicit ColorGraphics(Settings);

    Term::Color4 snake_color;
    Term::Color4 empty_color;
    Term::Color4 wall_color;
    Term::Color4 teleport_color;
    Term::Color4 bonus_color;
    Term::Color4 antibonus_color;
    Term::Color4 speed_bonus_color;
    Term::Color4 speed_antibonus_color;
};

// All values of Term::Color4 and theirs unsigned int expressions
// BLACK = 0
// RED = 1
// GREEN = 2
// YELLOW = 3
// BLUE = 4
// MAGENTA = 5
// CYAN = 6
// WHITE = 7
// GRAY = 60
// RED_BRIGHT = 61
// GREEN_BRIGHT = 62
// YELLOW_BRIGHT = 63
// BLUE_BRIGHT = 64
// MAGENTA_BRIGHT = 65
// CYAN_BRIGHT = 66
// WHITE_BRIGHT = 67
// DEFAULT = 9

// Graphic overrides

class SymGraphics : public Graphics {
   public:
    void print_empty_cell() override;
    void print_snake_cell() override;
    void print_snake_head_cell() override;
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
    void print_snake_cell() override;
    void print_snake_head_cell() override;
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
    void print_snake_cell() override;
    void print_snake_head_cell() override;
    void print_wall_cell() override;
    void print_teleport_cell() override;
    void print_bonus_cell() override;
    void print_antibonus_cell() override;
    void print_speed_bonus_cell() override;
    void print_speed_antibonus_cell() override;
};
