#include "settings.h"

Settings settings;

int parser(Settings &settings) {
    std::ifstream file("settings.txt");
    if (!file.is_open()) {
        return -1;
    }

    std::string var, map_length, map_width, speed, solid_wall, score, bonus_apples, view_mode, key_up, key_down, 
        key_left, key_right, teleport, key_pause;
    
    while(!file.eof()) {
        getline(file, var, '=');
        if (var == "map_length")  getline(file, map_length, '\n');
        if (var == "map_width")  getline(file, map_width, '\n');
        if (var == "speed")  getline(file, speed, '\n');
        if (var == "solid_wall")  getline(file, solid_wall, '\n');
        if (var == "score")  getline(file, score, '\n');
        if (var == "bonus_apples")  getline(file, bonus_apples, '\n');
        if (var == "teleport")  getline(file, teleport, '\n');
        if (var == "view_mode") getline(file, view_mode, '\n');
        if (var == "key_up") getline(file, key_up, '\n');
        if (var == "key_down") getline(file, key_down, '\n');
        if (var == "key_left") getline(file, key_left, '\n');
        if (var == "key_right") getline(file, key_right, '\n');
        if (var == "key_pause") getline(file, key_pause, '\n');
    }

    settings.map_length = stoi(map_length); 
    settings.map_width = stoi(map_width);
    settings.speed = stof(speed); 
    settings.solid_wall = stoi(solid_wall);
    settings.score = stoi(score);
    settings.bonus_apples = stoi(bonus_apples);
    settings.teleport = stoi(teleport);
    settings.view_mode = stoi(view_mode);
    settings.key_up = stoi(key_up);
    settings.key_down = stoi(key_down);
    settings.key_left = stoi(key_left);
    settings.key_right = stoi(key_right);
    settings.key_pause = stoi(key_pause);

    file.close();
    return 0;
}