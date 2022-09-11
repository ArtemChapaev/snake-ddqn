#include <Settings.h>

class MapModel {
private:

    Cell** field; // динамический двумерный массив для карты

    unsigned width; // ширина карты

    unsigned length; // длина карты

public:

    MapModel(unsigned, unsigned); // конструктор инициализации по длине ширине

    void put_snake(Snake); // отметить координаты змеи на карте

    void clear_cell(unsigned, unsigned); // очистка блока 

    Cell check_cell(unsigned, unsigned); // проверка блока

    unsigned get_width(); // ширина карты

    unsigned get_length(); // длина карты

    Cell get_block(unsigned, unsigned); // клетка карты по указанным координатам

    //~MapModel(); // неработающий деструктор

};