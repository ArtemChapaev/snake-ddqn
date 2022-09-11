struct Settings {
    unsigned mapWidth, mapLength;
    bool solidWall;
    unsigned speed;
    unsigned score;
    bool record;
    bool bonusApples;
};

enum Cell {EMPTY, SNAKE, WALL, FRUIT};
