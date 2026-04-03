#include "IScene.h"
#include "menuScene.h"
#include "gameScene.h"
#include "netScene.h"
#include "lobbyScene.h"

class SceneManager{
    private:
    IScene* currScene;
    public:
    SceneManager(){currScene = new LobbyScene;};
    ~SceneManager(){delete currScene; currScene = nullptr;};
    void displayScene(sf::RenderWindow &window){currScene->draw(window);};
    IScene* getScene(){return currScene;};

    void processAction(SceneAction action){
        switch (action) {

        case SceneAction::startGame:
            if(MenuScene* menu = dynamic_cast<MenuScene*>(currScene)){
                Difficulty d = menu->getDiff();
                delete currScene;
                currScene = new GameScene(d);
            }
            break;
        
        case SceneAction::goToMenu:
            delete currScene;
            currScene = new MenuScene();
            break;

        case SceneAction::goToNetworking:
            delete currScene;
            currScene = new NetScene();
            break;

        case SceneAction::startLobby:
            std::cout << "hosting";
            break;

        case SceneAction::searchLobby:
            std::cout << "searching";
            break;
        default:
            break;
        }
    };
};