#include <SFML/Graphics.hpp>
#include "menu.h"

int main()
{   
    sf::RenderWindow window(sf::VideoMode({500, 600}), "Minesweeper Client");
    Menu m;
    float bombDensity = 0.12;
    int rows = 16;
    int columns = 16;
    
    m.createBoard(rows, columns, round(rows*columns*bombDensity));
    m.drawMenu(window);
    return 0;
}