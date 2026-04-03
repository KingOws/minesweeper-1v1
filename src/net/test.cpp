/*#include "lobbydiscovery.h"
#include <iostream>

int main() {
    LobbyDiscovery discovery;
    bool isHost = true; // change to false on the other machine

    if (isHost) {
        std::cout << "Broadcasting...\n";
        while (true) {
            discovery.broadcastPresence(2550);
            sf::sleep(sf::seconds(1));
        }
    } else {
        discovery.bindForListening();
        std::cout << "Listening...\n";
        while (true) {
            HostEntry entry;
            if (discovery.pollForHosts(entry)) {
                std::cout << "Found host: " << entry.ip << ":" << entry.gamePort << "\n";
            }
        }
    }
}*/