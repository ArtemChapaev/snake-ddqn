#include <Settings.h>
#include <MapModel.h>

class MapView {
private:

    MapModel map; // объект класса карты

    // graphics

public:

    MapView(MapModel map) : map {map} {}; // список инициализации

    void print(); // вывод карты
    
};