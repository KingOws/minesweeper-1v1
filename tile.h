#pragma once


class Tile{
    private:
    int pos_x;
    int pos_y;

    public:
    Tile();
    ~Tile();

    void drawTile();
    inline int getPos_x(){return pos_x;};
    inline int getPos_y(){return pos_y;};
};