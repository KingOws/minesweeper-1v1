#pragma once
#include "IScene.h"
#include "menuScene.h"
#include "gameScene.h"
#include "netScene.h"
#include "mainMenuScene.h"
#include "lobbyBrowsingScene.h"
#include <iostream>

class SceneManager {
private:
    sf::RenderWindow* window;
    IScene* currScene;
    IScene* nextScene; // Pointer to hold the scene we want to switch to
    bool shouldSwap;   // Flag to signal a swap is needed

    // Helper to print results if we are leaving a GameScene
    void checkGameResults() {
        if (GameScene* game = dynamic_cast<GameScene*>(currScene)) {
            // Note: You need to ensure GameScene or Board has public 
            // accessors for these, or check them inside GameScene::update
            std::cout << "\n--- Session Ended ---" << std::endl;
            // Accessing the board logic before we delete it
            // Assuming you update GameScene to keep the board until destruction
        }
    }

public:
    SceneManager() : nextScene(nullptr), shouldSwap(false) {
        currScene = new MainMenuScene();
    }

    ~SceneManager() {
        delete currScene;
        if (nextScene) delete nextScene;
    }

    // Call this at the end of your main loop in driver.cpp
    void updateAndSwap() {
        // Run the current scene's internal logic
        currScene->update();

        // Perform the swap only when it is safe (not inside an event handler)
        if (shouldSwap) {
            delete currScene;
            currScene = nextScene;
            nextScene = nullptr;
            shouldSwap = false;
            std::cout << "[SceneManager] Scene transition complete.\n";
        }
    }

    void displayScene(sf::RenderWindow& window) {
        if (currScene) currScene->draw(window);
    }

    IScene* getScene() { return currScene; }

    void processAction(SceneAction action, sf::RenderWindow &window) {
        if (action == SceneAction::None) return;

        IScene* tempNext = nullptr;

        switch (action) {
        case SceneAction::startGame:
            if (MenuScene* menu = dynamic_cast<MenuScene*>(currScene)) {
                tempNext = new GameScene(menu->getDiff(), window);
                std::cout << "[SceneManager] Starting New Game...\n";
            }
            break;

        case SceneAction::goToMenu:
            // Check results before leaving GameScene
            if (GameScene* game = dynamic_cast<GameScene*>(currScene)) {
                // Here we print to terminal based on the final state
                // This assumes you removed the 'delete board' logic from GameScene::update
                std::cout << "Returning to Menu. Game finalized.\n";
            }
            tempNext = new MenuScene();
            break;

        case SceneAction::goToNetworking:
            tempNext = new NetScene();
            break;

        case SceneAction::startLobby:
            tempNext = new MenuScene("hosting"); 
            break;

        case SceneAction::searchLobby:
            tempNext = new LobbyBrowsingScene();
            break;

        case SceneAction::goToMainMenu:
            tempNext = new MainMenuScene(window);
            break;

        case SceneAction::Exit:
            // Handle exit if needed
            break;

        default:
            break;
        }

        if (tempNext) {
            nextScene = tempNext;
            shouldSwap = true;
        }
    }
};