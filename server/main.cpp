#include <iostream>
#include <SFML/Network.hpp>
#include <vector>
#include "gameServer.h"


int main(){
    //The server
    int PORT = 55001;
    GameServer server(55001);

    while(server.isOn()){
        if(server.getSelector().wait(sf::milliseconds(10))){
        server.acceptConnections();
        server.authenticatePlayers();
        server.receivePackets();
        server.sendPackets();
        }
    }
}