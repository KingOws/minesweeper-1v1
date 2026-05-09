#include "lobbyhosting.h"


LobbyHosting::LobbyHosting(){
    clientList.push_back(std::move(socket));
    hosting = true;

    listener.listen(PORT);
    selector.add(listener);
}

void LobbyHosting::runServer(){
    if(selector.wait(sf::milliseconds(10))){
        if(selector.isReady(listener)){

        }
    }
}


LobbyHosting::~LobbyHosting() {}