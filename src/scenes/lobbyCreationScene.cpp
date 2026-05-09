#include "lobbycreationScene.h"


LobbyCreationScene::LobbyCreationScene(LobbyInfo& g) : MenuScene(), hostingInfo(g){
    hostingInfo.hosting = true;
    std::cout << "hosting" << std::endl;
}

void LobbyCreationScene::updateNet(){
    if(ld){
        ld->runServer();
        ld->updatePackets();
        ld->sendPackets();
        ld->receivePackets();
    }
}

LobbyCreationScene::~LobbyCreationScene() = default;