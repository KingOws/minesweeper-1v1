#pragma once
#include <SFML/Graphics.hpp>

class Tile{
    private:

    static const int size = 1;
    int pos_x;
    int pos_y;
    bool flag;
    bool bomb;
    int value;

    public:
    Tile();
    Tile(int pos_x, int pos_y, bool isBomb);
    ~Tile();

    void drawTile(sf::RenderWindow& window);
    inline int getPos_x() const {return pos_x;};
    inline int getPos_y() const {return pos_y;};
    inline bool isBomb() const {return bomb;}

    inline void setValue(int v) {value = v;}
};