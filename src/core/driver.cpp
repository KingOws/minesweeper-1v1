#include <SFML/Graphics.hpp>
#include "SceneManager.h"
#include <thread>
#include <atomic>

void gameRun(sf::RenderWindow&, SceneManager&);
void networkRun(SceneManager&, std::atomic<bool>&);

int main()
{   
    sf::Image icon;
    if (!icon.loadFromFile("../images/icon.png")) {
        std::cerr << "Failed to load icon.png" << std::endl;
        return -1;
    }

    sf::RenderWindow window(sf::VideoMode({800, 600}), "Minesweeper Client");
    window.setIcon(icon);

    SceneManager sm;

    std::atomic<bool> serverRunning{true};
    
    std::thread t2(networkRun, std::ref(sm), std::ref(serverRunning));

    gameRun(window, sm);

    serverRunning = false;
    t2.join();
    return 0;
}

void gameRun(sf::RenderWindow& window, SceneManager& sm){
    while (window.isOpen()){
        while (auto event = window.pollEvent()){
            const sf::Event& e = *event;
            if (event->is<sf::Event::Closed>()){
                window.close();
            }

            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::A) {
                    // A was pressed — trigger your autocomplete here
                    if(GameScene* g = dynamic_cast<GameScene*>(sm.getScene())){
                        g->handleDevWin();
                    }
                }
                if(keyPressed->code == sf::Keyboard::Key::Escape){
                    sm.processAction(sm.getScene()->handleEsc(), window);
                }
            }
            if(event->is<sf::Event::MouseButtonPressed>()){
                const sf::Event::MouseButtonPressed* mouseEvent = event->getIf<sf::Event::MouseButtonPressed>();
                if(mouseEvent->button == sf::Mouse::Button::Left){
                    sf::Vector2f mousePos = window.mapPixelToCoords({mouseEvent->position.x, mouseEvent->position.y});
                    sm.processAction(sm.getScene()->handleLeftEvent(mousePos),window);
                }
                if(mouseEvent->button == sf::Mouse::Button::Right){
                    sf::Vector2f mousePos = window.mapPixelToCoords({mouseEvent->position.x, mouseEvent->position.y});
                    sm.processAction(sm.getScene()->handleRightEvent(mousePos),window);
                }
            }
        }

        sm.updateAndSwap();
        window.clear({255, 255, 255, 255});
        sm.displayScene(window);
        window.display();
    }
}

void networkRun(SceneManager& sm, std::atomic<bool>& serverRunning) {
    // permaruns
    while (serverRunning) { 
        //checks if a lobby Manager object has been created
        std::shared_ptr<Lobby> lobManager = sm.getLobbyManager();
        if(lobManager){
            //polymorphism so no dynamic casting needed cuz apparenlty its inedfificnet
            lobManager->establishConnection(serverRunning);

            //does normal packet stuff
            lobManager->updatePackets();
            lobManager->receivePackets();
            lobManager->sendPackets();
        }

        //apparently has to sleep if not ur computer will blow up
        sf::sleep(sf::milliseconds(10));
    }
}

    