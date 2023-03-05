#include <cstring>

#include "game.h"
#include "menu.h"

int main(int argc, char** argv) {
    bool random_apples = true;
    std::string filename = "settings.txt";

    if (argc == 2 && !strcmp(argv[1], "-a")) {
        random_apples = false;
    } else {
        for (int i = 0; i < argc; ++i)
            if (!strcmp(argv[i], "-a")) {
                random_apples = false;
            } else if (!strcmp(argv[i], "-f") && i + 1 < argc) {
                filename = argv[i + 1];
            }
    }

    std::cout << "\033[3J\033[H\033[2J";

    std::stack<std::unique_ptr<Menu>> menus;  // stores opened menus hierarchy

    unsigned string_num = 0;  // stores which menu option is selected
    unsigned prev_string_num = string_num;
    bool is_exit = false;

    Menu* m = new MainMenu(filename, random_apples);
    menus.push(std::unique_ptr<Menu>(m));
    menus.top().get()->draw(string_num);
    while (is_exit != 1) {
        is_exit = menus.top().get()->update(string_num, menus);
        if (string_num != prev_string_num) {
            menus.top().get()->draw(string_num);
            prev_string_num = string_num;
        }
    }

    std::cout << "\033[3J\033[H\033[2J";

    return 0;
}
