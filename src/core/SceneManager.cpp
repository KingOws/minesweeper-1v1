#include "SceneManager.h"

SceneManager::SceneManager(){

}

SceneManager::~SceneManager(){

}

void SceneManager::handleEvent(sf::Event& event){
    swapScenes(currScene->handleEvent(event));
}

void SceneManager::swapScenes(ChangeScenes sceneChange){
    std::unique_ptr<IScene> nextScene;

    switch(sceneChange){
        case MAIN_MENU:
            nextScene = std::make_unique<MainMenuScene>();
            break;
        case DIFF_SELECT:
            nextScene = std::make_unique<MenuScene>();
            break;
        case IN_GAME:
            nextScene = createGame();
            break;
        case SEARCHING_GAME:
            nextScene = std::make_unique<>();
            break;
        case GO_BACK:
            nextScene = std::move(history.top());
            history.pop();
            break;
        default:
            return;
    }
    if(currScene && sceneChange != GO_BACK)
        history.push(std::move(currScene));

    currScene = std::move(nextScene);
}

std::unique_ptr<IScene> SceneManager::createGame(){
    Difficulty diff = Difficulty::hard;

    if(MenuScene* menu = static_cast<MenuScene*>(currScene.get()))
        diff = menu->getDifficulty();
    auto nextScene = std::make_unique<GameScene>(diff);
    return nextScene; 
}

void SceneManager::displayScene(sf::RenderWindow& window){
    if(currScene)
        currScene->draw(window);
}

