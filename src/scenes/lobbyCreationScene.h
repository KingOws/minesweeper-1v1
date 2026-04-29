#pragma once
#include "menuScene.h"

class LobbyDiscovery;

class LobbyCreationScene : public MenuScene{
    private:
        std::unique_ptr<LobbyDiscovery> ld;
        LobbyInfo hostingInfo;

    public:
        LobbyCreationScene();
        ~LobbyCreationScene();
        virtual void update();

};