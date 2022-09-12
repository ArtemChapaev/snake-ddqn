#pragma once

#include "mapModel.h"

class Graphics {
public:
    virtual void print_empty_cell() = 0;
    virtual void print_snake_cell() = 0;
    virtual void print_snake_head_cell() = 0;
    virtual void print_wall_cell() = 0;
    virtual void print_fruit_cell() = 0;
};


class SymGraphics : public Graphics {
public:
    void print_empty_cell() override;
    void print_snake_cell() override;
    void print_snake_head_cell() override;
    void print_wall_cell() override;
    void print_fruit_cell() override;
};

class MapView {
public:
    MapView(MapModel map);
    ~MapView();
    void print();

private:
    MapModel map;
    Graphics *graphics;
};