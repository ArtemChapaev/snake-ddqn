#include <MapView.h>
#include <iostream>

using namespace std;

void MapView::print() {
    for (int i = 0; i < map.get_width(); i++) {
            for (int j = 0; j < map.get_length(); j++) {
                switch(map.get_block(i, j)) {
                    case EMPTY:
                        cout << " ";
                        break;
                    case SNAKE:
                        cout << "O";
                        break;
                    case WALL:
                        cout << "*";
                        break;
                    case FRUIT:
                        cout << "X";
                        break;
                }
            }
            cout << endl;
        }
}