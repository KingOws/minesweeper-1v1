#include "lobbycreationScene.h"


LobbyCreationScene::LobbyCreationScene() : MenuScene(){
    hostingInfo.hosting = true;
    ld = std::make_unique<LobbyDiscovery>(hostingInfo);
}

void LobbyCreationScene::update(){
    if(ld){
        ld->updatePackets();
        ld->sendPackets();
        ld->receivePackets();
    }
}

LobbyCreationScene::~LobbyCreationScene() = default;