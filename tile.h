#pragma once
#include <SFML/Graphics.hpp>

class Tile{
    private:
    bool exists;
    static const int size = 25;
    int pos_x;
    int pos_y;
    bool flag;
    bool bomb;
    bool opened;
    int value;
    sf::RectangleShape rect;

    public:
    Tile();
    Tile(int pos_x, int pos_y, bool isBomb);
    ~Tile();

    void drawTile(sf::RenderWindow& window);
    inline int getPos_x() const {return pos_x;};
    inline int getPos_y() const {return pos_y;};
    inline bool isBomb() const {return bomb;};
    inline void setBomb(bool b) {bomb = b;};
    inline void setPos_x(int p) {pos_x = p;};
    inline void setPos_y(int p) {pos_y = p;};
    void updateRect();

    inline void setValue(int v) {value = v;};
};