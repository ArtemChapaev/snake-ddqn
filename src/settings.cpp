#include "settings.h"

int parser(Settings &settings, std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return -1;
    }

    std::string var, map_length, map_width, speed, solid_wall, score, bonus_apples, view_mode, reset_length, key_up,
            key_down, key_left, key_right, key_pause, key_enter, key_teleport, key_wall, key_empty, snake_color,
            empty_color, wall_color, teleport_color, bonus_color, antibonus_color, speed_bonus_color,
            speed_antibonus_color;
    
    try
    {
    while (!file.eof()) {

        getline(file, var, '=');
        if (var == "map_length") getline(file, map_length);
        if (var == "map_width") getline(file, map_width);
        if (var == "speed") getline(file, speed);
        if (var == "solid_wall") getline(file, solid_wall);
        if (var == "score") getline(file, score);
        if (var == "bonus_apples") getline(file, bonus_apples);
        if (var == "view_mode") getline(file, view_mode);
        if (var == "reset_length") getline(file, reset_length);
        if (var == "key_up") getline(file, key_up);
        if (var == "key_down") getline(file, key_down);
        if (var == "key_left") getline(file, key_left);
        if (var == "key_right") getline(file, key_right);
        if (var == "key_pause") getline(file, key_pause);
        if (var == "key_enter") getline(file, key_enter);
        if (var == "key_teleport") getline(file, key_teleport);
        if (var == "key_wall") getline(file, key_wall);
        if (var == "key_empty") getline(file, key_empty);
        if (var == "snake_color") getline(file, snake_color);
        if (var == "empty_color") getline(file, empty_color);
        if (var == "wall_color") getline(file, wall_color);
        if (var == "teleport_color") getline(file, teleport_color);
        if (var == "bonus_color") getline(file, bonus_color);
        if (var == "antibonus_color") getline(file, antibonus_color);
        if (var == "speed_bonus_color") getline(file, speed_bonus_color);
        if (var == "speed_antibonus_color") getline(file, speed_antibonus_color);
    }

    settings.map_length = stoi(map_length);
    settings.map_width = stoi(map_width);
    settings.speed = stof(speed);
    settings.solid_wall = stoi(solid_wall);
    settings.score = stoi(score);
    settings.bonus_apples = stoi(bonus_apples);
    settings.view_mode = stoi(view_mode);
    settings.reset_length = stoi(reset_length);
    settings.key_up = stoi(key_up);
    settings.key_down = stoi(key_down);
    settings.key_left = stoi(key_left);
    settings.key_right = stoi(key_right);
    settings.key_pause = stoi(key_pause);
    settings.key_enter = stoi(key_enter);
    settings.key_teleport = stoi(key_teleport);
    settings.key_wall = stoi(key_wall);
    settings.key_empty = stoi(key_empty);
    settings.snake_color = Term::Color4(stoi(snake_color));
    settings.empty_color = Term::Color4(stoi(empty_color));
    settings.wall_color = Term::Color4(stoi(wall_color));
    settings.teleport_color = Term::Color4(stoi(teleport_color));
    settings.bonus_color = Term::Color4(stoi(bonus_color));
    settings.antibonus_color = Term::Color4(stoi(antibonus_color));
    settings.speed_bonus_color = Term::Color4(stoi(speed_bonus_color));
    settings.speed_antibonus_color = Term::Color4(stoi(speed_antibonus_color));

    file.close();
    }
    catch (const std::exception ex)
    {
        std::ofstream temp;
        temp.open("temp.txt");

        temp<<R"(map_length=20
map_width=20
solid_wall=0
score=1
bonus_apples=1
view_mode=2
reset_length=0
key_up=72
key_left=75
key_down=80
key_right=77
key_pause=27
key_enter=10
key_teleport=116
key_wall=119
key_empty=101
snake_color=2
empty_color=0
wall_color=60
teleport_color=67
bonus_color=1
antibonus_color=3
speed_bonus_color=4
speed_antibonus_color=5
speed=2
)";

        temp.close();
        file.close();
        
        const char *p = filename.c_str();
        remove(p);
        rename("temp.txt", p);
    }
    return 0;
}

void replace_setting(std::string path, std::string erase_line, unsigned new_value) {
    std::string option;
    std::string value;
    std::ifstream fin;

    fin.open(path);
    std::ofstream temp;
    temp.open("temp.txt");

    while (getline(fin, option, '=')) {
        getline(fin, value);
        if (option != erase_line)
            temp << option << "=" << value << std::endl;
    }

    temp << erase_line << "=" << new_value << std::endl;

    temp.close();
    fin.close();

    const char *p = path.c_str();
    remove(p);
    rename("temp.txt", p);
}

void replace_float_setting(std::string path, std::string erase_line, float new_value) {
    std::string option;
    std::string value;
    std::ifstream fin;

    fin.open(path);
    std::ofstream temp;
    temp.open("temp.txt");

    while (getline(fin, option, '=')) {
        getline(fin, value);
        if (option != erase_line)
            temp << option << "=" << value << std::endl;
    }

    temp << erase_line << "=" << new_value << std::endl;

    temp.close();
    fin.close();

    const char *p = path.c_str();
    remove(p);
    rename("temp.txt", p);
}

void replace_char_setting(std::string path, std::string erase_line, char new_value) {
    std::string option;
    std::string value;
    std::ifstream fin;

    fin.open(path);
    std::ofstream temp;
    temp.open("temp.txt");

    while (getline(fin, option, '=')) {
        getline(fin, value);
        if (option != erase_line)
            temp << option << "=" << value << std::endl;
    }

    temp << erase_line << "=" << (int) new_value << std::endl;

    temp.close();
    fin.close();

    const char *p = path.c_str();
    remove(p);
    rename("temp.txt", p);
}

void copy_file(std::string from, std::string to) {
    std::ifstream src(from);
    std::ofstream dst(to);
    dst << src.rdbuf();
    src.close();
    dst.close();
}