#pragma once

#include "mapModel.h"
#include "graphics.h"

class MapView {
public:
    MapView(MapModel &map, Settings);
    ~MapView();
    void print();
private:
    MapModel &map;
    Graphics *graphics;
};
