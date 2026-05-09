#include "lobbyhosting.h"


LobbyHosting::LobbyHosting(){
    clientList.push_back(std::move(socket));
    hosting = true;

    listener.listen(PORT);
    selector.add(listener);
}

void LobbyHosting::runServer(){
    hosting = true;
    while(hosting){
        if(selector.wait()){
            if(selector.isReady(listener)){

            }
        }
    }
}


LobbyHosting::~LobbyHosting() {}