#pragma once
#include "menuScene.h"
#include "lobbyhosting.h"

class LobbyCreationScene : public MenuScene{
    private:
        std::unique_ptr<LobbyHosting> ld;
        LobbyInfo& hostingInfo;

    public:
        LobbyCreationScene(LobbyInfo& g);
        ~LobbyCreationScene();
        void updateNet();

        std::unique_ptr<LobbyHosting> getLobbyHosting(){return std::move(ld);};
};