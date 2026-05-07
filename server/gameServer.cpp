#include "gameServer.h"


GameServer::GameServer(){}

GameServer::GameServer(int p) : PORT(p), on(true) {
    //Set up listener with port
    listener.setBlocking(false);
    if (listener.listen(PORT) != sf::Socket::Status::Done) {
        std::cerr << "Port " << PORT << " not available" << std::endl;
        exit(1);
    }

    // Add the listener to the selector so we know when someone is knocking
    selector.add(listener); 
    std::cout << "Listening on port: " << PORT << std::endl;
}

void GameServer::acceptConnections(){
    //std::cout << "accepting connetions" << std::endl;
        //check if new player is connecting
        if(selector.isReady(listener)){
            auto newSocket = std::make_unique<sf::TcpSocket>();

            //check if socket is accepted
            if(listener.accept(*newSocket) == sf::Socket::Status::Done){
                newSocket->setBlocking(false);
                std::cout << "New connection from: " << newSocket->getRemoteAddress()->toString() << std::endl;
                selector.add(*newSocket);
                pendingSockets.push_back(std::move(newSocket));
                std::cout << "Added socket to pending sockets!" << std::endl;
            }
        }
}

void GameServer::authenticatePlayers() {
    for (auto it = pendingSockets.begin(); it != pendingSockets.end(); ) {
        sf::TcpSocket& clientSocket = **it;
        std::cout << "Checking socket..." << std::endl;
        if (selector.isReady(clientSocket)) {
            std::cout << "Socket is ready!" << std::endl;
            sf::Packet packet;
            sf::Socket::Status status = clientSocket.receive(packet);

            if (status == sf::Socket::Status::Done) {
                LobbyInfo lobbyInfo;
                if (!(packet >> lobbyInfo)) {
                    // Handle corrupted packet: remove and skip
                    selector.remove(clientSocket);
                    it = pendingSockets.erase(it);
                    continue;
                }
                selector.remove(clientSocket);
                std::unique_ptr<sf::TcpSocket> movingSocket = std::move(*it);
                std::unique_ptr<Player> newPlayer = std::make_unique<Player>(std::move(movingSocket), lobbyInfo, true);
                selector.add(*(newPlayer->socket));
                players.push_back(std::move(newPlayer));
                std::cout << "Added player to player list" << std::endl;
                it = pendingSockets.erase(it);
                continue; 
            }
            else if (status == sf::Socket::Status::Disconnected || status == sf::Socket::Status::Error) {
                std::cout << "Pending client disconnected." << std::endl;
                selector.remove(clientSocket);
                it = pendingSockets.erase(it);
                continue; // Move to next without hitting it++
            }
        }
        
        // Only increment if we didn't remove the current element
        ++it;
    }
}

void GameServer::sendPackets(){
    for(auto it = players.begin(); it != players.end(); it++){
        (*it)->socket->setBlocking(false);
        sf::Packet playerPacket;
        playerPacket << (*it)->info;
        sf::Socket::Status status = (*it)->socket->send(playerPacket);
        if(status == sf::Socket::Status::Done){
            //std::cout << "Packet sent!" << std::endl;
        }
    }
}

void GameServer::receivePackets(){
    for(auto it = players.begin(); it != players.end();){
        (*it)->socket->setBlocking(false);
        if(selector.isReady(*((*it)->socket))){
            sf::Socket::Status status = (*it)->socket->receive(currentPacket);
            //if the socket receiving is done
            if(status == sf::Socket::Status::Done){
                //std::cout << "Packet received!" << std::endl;
                handlePackets(**it);
                it++;
            }
            //if the socket status is disconnected or error just remove it lol
            else if(status == sf::Socket::Status::Disconnected || status == sf::Socket::Status::Error){
                std::cout << "Error receiving packet" << std::endl;
                selector.remove(*((*it)->socket));
                pruneStaleGame((*it).get());
                it = players.erase(it);

            //skip it socket if anythign else
            }else{
                it++;
            }
        //if the socket is not ready just go onto the next thing
        }else{
            it++;
        }
    }
} 

void GameServer::handlePackets(Player& currPlayer){
    bool alreadyCreated = currPlayer.info.gameCreated;
    currentPacket >> currPlayer.info;
    
    //have to do this because client was sending their packets too fast
    if(alreadyCreated)
        currPlayer.info.gameCreated = true;
    //when player is hosting
    if (currPlayer.info.hosting && !currPlayer.info.gameCreated) {
        games.emplace_back(std::make_unique<Game>());
        auto& newGame = games.back();
        currPlayer.info.lobbyId  = newGame->getId();
        currPlayer.info.availableGames = pactor<int>{};
        currPlayer.info.gameCreated = true;
        //passes raw pointer to game
        newGame->addPlayer(&currPlayer);


    //When player is searching for game
    } else if(!currPlayer.info.hosting && !currPlayer.info.inGame){
        currPlayer.info.availableGames = gamesToInt(games);

    //when player is attempting to join game
    } else if (!currPlayer.info.hosting && currPlayer.info.lobbyId != -1) {
        Game* game = getGame(currPlayer.info.lobbyId);
        if (!game){
            std::cout << "Player tried to join Game that doesn't exist!" << std::endl;
            return;
        }
        if(game->getNumPlayers() >= game->getMaxPlayers()){
            std::cout << "Player tried to join full Game" << std::endl;
            return;
        }

        game->addPlayer(&currPlayer);
    }
}

Game* GameServer::getGame(int gId){
    for(size_t i = 0; i < games.size(); i++){
        if(games[i]->getId() == gId)
            return games[i].get();
    }
    return nullptr;
}   


GameServer::~GameServer(){

}

void GameServer::createGame(){

}

void GameServer::pruneStaleGame(const Player& currPlayer){
    int gameIdToKill;
    if(currPlayer.info.hosting && currPlayer.info.gameCreated){
        gameIdToKill = currPlayer.info.lobbyId;
        std::erase_if(games, [gameIdToKill](const std::unique_ptr<Game>& g){
             return (g->getId() == gameIdToKill);
        });
        std::cout << "Hosted game " << gameIdToKill << " deleted." << std::endl;
    }
}
