#pragma once
#include <SFML/Graphics.hpp>
#include "spritemanager.h"
#include <iostream>

class Tile{
    private:
    bool exists;
    static const int size = 32;
    static sf::Texture defaultTexture;
    static bool loaded;
    float pos_x;
    float pos_y;
    bool flag;
    bool bomb;
    bool opened;
    int value;
    sf::Sprite sprite;

    public:
    Tile();
    Tile(int pos_x, int pos_y, bool isBomb);
    ~Tile();

    void drawTile(sf::RenderWindow& window);
    inline float getPos_x() const {return pos_x;};
    inline float getPos_y() const {return pos_y;};
    inline int getValue() const {return value;};
    inline bool isBomb() const {return bomb;};
    inline bool isFlagged() const {return flag;};
    inline bool isOpened() const {return opened;};
    static int getSize() {return size;};

    inline void setBomb(bool b) {bomb = b;};
    inline void setPos_x(float p) {pos_x = p;};
    inline void setPos_y(float p) {pos_y = p;};
    inline void setOpened(bool s) {opened = s;};
    inline void setFlag(bool f) {flag = f;};

    void loadDefaultTexture();
    void updateSprite(const SpriteManager& manager, bool reveal=false);

    inline void setValue(int v) {value = v;};
};