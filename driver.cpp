#include <SFML/Graphics.hpp>
#include "menu.h"

int main()
{   
    Menu m;
    float bombDensity = 0.12;
    int rows = 16;
    int columns = 16;
    m.createBoard(rows, columns, round(rows*columns*bombDensity));
    m.drawMenu();
    return 0;
}