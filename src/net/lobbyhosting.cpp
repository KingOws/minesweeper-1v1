#include "lobbyhosting.h"


LobbyHosting::LobbyHosting() : Lobby(){
    broadcastTimer.start();
    hosting = true;
    lobbyInfo.inGame = false;
    lobbyInfo.seed = std::random_device{}();

    //creates the host player
    //players.emplace_back(std::in_place, std::move(this->socket), 1, false);

    sf::Socket::Status status = listener.listen(GAME_PORT);
    if(status == sf::Socket::Status::Done){
        std::cout << "Host is listening on port " << GAME_PORT << std::endl;
        selector.add(listener);
    }
    else if(status == sf::Socket::Status::Error)
        std::cout << "Error adding listener to gameport";
}

void LobbyHosting::establishConnection(std::atomic<bool>&  running){
    //if (isPlayerIPEmpty()) return;
    this->runServer();

    if(lobbyInfo.currentPlayers < lobbyInfo.maxPlayers){
        sf::Packet beacon;
        //sends a beacon signal using broadcast address basically letting everyone know what the host address is
        if(broadcastTimer.getElapsedTime() > sf::seconds(1.0f)){
            udpListener.send(beacon, sf::IpAddress::Broadcast, DiscoveryPort);
            broadcastTimer.restart();
        }
    }   
}

void LobbyHosting::runServer(){
    if(selector.wait(sf::milliseconds(10))){
        if(selector.isReady(listener)){
            auto newSocket = std::make_unique<sf::TcpSocket>();

            if(listener.accept(*newSocket) == sf::Socket::Status::Done){

                if(lobbyInfo.currentPlayers >= lobbyInfo.maxPlayers || lobbyInfo.inGame){
                    std::cout << "Lobby full or in game, rejecting client" << std::endl;
                    newSocket->disconnect();

                } else {
                    std::cout << "Client connected: " << newSocket->getRemoteAddress().value() << std::endl;
                    players.emplace_back(std::in_place, std::move(newSocket), ++lobbyInfo.currentPlayers);
                    selector.add(*players.back()->socket);
                    tcpLinkReady = true;
                }
            }
        }
    }
}


void LobbyHosting::shutdown(){
    for(auto& player : players){
        selector.remove(*player->socket);
        player->socket->disconnect();
    }
    players.clear();
    selector.remove(listener);
    listener.close();
    listener = sf::TcpListener{};
    hosting = false;
}


LobbyHosting::~LobbyHosting() {
    if (hosting) shutdown();
}

void LobbyHosting::sendPackets(){
    packet.clear();
    for (auto it = players.begin(); it != players.end(); it++) {
        switch(playerAction.inGame){
            case false:
                packet << lobbyInfo;
                packet << (*it)->playerAction->playerId << (*it)->playerAction->inGame;
                break;
            case true:
                packet << gameUpdate;
                packet << (*it)->playerAction->playerId << (*it)->playerAction->inGame;
                break;
        }
        if(packet.getDataSize() == 0) return;
        sf::Socket::Status status = (*it)->socket->send(packet);
        if(status == sf::Socket::Status::Done)
            //std::cout << "Package Sent to " << (*it)->socket->getRemoteAddress()->toString() << "!\n";
            std::cout << "";
        else if(status == sf::Socket::Status::Error)
            std::cerr << "Big error\n";
    }
}

void LobbyHosting::receivePackets(){
    for (auto it = players.begin(); it != players.end();) {
        if (selector.isReady(*((*it)->socket))) {
            sf::Socket::Status status = (*it)->socket->receive(packet);

            if (status == sf::Socket::Status::Done) {
                if(lobbyInfo.inGame == true){
                    //std::cout << "Received from " << (*it)->socket->getRemoteAddress()->toString() << '\n';
                    handlePlayerPackets(*(*it));
                    packet.clear();
                    ++it;
                }
            } else if (status == sf::Socket::Status::Disconnected || status == sf::Socket::Status::Error) {
                lobbyInfo.currentPlayers--;
                std::cout << "Client disconnected: " << (*it)->socket->getRemoteAddress()->toString() << '\n';
                selector.remove(*((*it)->socket));
                it = players.erase(it);
            }else
                ++it;
        }else
            ++it;
    }
}

void LobbyHosting::handlePlayerPackets(PlayerInfo& player){
    packet >> player.playerAction->clickPos >> player.playerAction->isRightClick;

    gameUpdate.tilePos.x = (player.playerAction->clickPos.x-gScene.getOffset().x)/Tile::getSize();
    gameUpdate.tilePos.y = (player.playerAction->clickPos.y-gScene.getOffset().y)/Tile::getSize();

    if(player.playerAction->isRightClick)
        player.board->placeFlag(gameUpdate.tilePos);
    
    if(!player.playerAction->isRightClick)
        player.board->revealTile(gameUpdate.tilePos);

    player.gameUpdate->won = player.board->getWon();
    player.gameUpdate->lost = player.board->getLost();

    std::cout << player.board->getWon();
}