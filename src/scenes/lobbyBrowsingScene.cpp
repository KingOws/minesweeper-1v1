#include "lobbybrowsingscene.h"
#include <iostream>

LobbyBrowsingScene::LobbyBrowsingScene() {
    if (!font.openFromFile("../src/fonts/arial.ttf"))
        std::cerr << "Error: could not load font" << std::endl;

    ld = LobbyDiscovery::createJoiner();
    std::cout << "joining...";
}

LobbyBrowsingScene::~LobbyBrowsingScene() {}

void LobbyBrowsingScene::update() {
    ld->tick(hosts);

    boxes.clear();
    textFields.clear();

    float posx = 100, posy = 150;
    for (const HostEntry& h : hosts) {
        sf::RectangleShape rect;
        rect.setSize({600, 100});
        rect.setFillColor({75, 175, 75, 75});
        rect.setPosition({posx, posy});
        posy += 150;

        sf::Text text(font);
        text.setString(h.ip + ":" + std::to_string(h.gamePort));
        text.setCharacterSize(36);
        text.setFillColor(sf::Color::Black);

        sf::FloatRect bounds = text.getLocalBounds();
        text.setOrigin({bounds.position.x + bounds.size.x / 2.f,
                        bounds.position.y + bounds.size.y / 2.f});
        text.setPosition({rect.getPosition().x + rect.getSize().x / 2.f,
                          rect.getPosition().y + rect.getSize().y / 2.f});

        boxes.push_back(rect);
        textFields.push_back(text);
    }
}

void LobbyBrowsingScene::draw(sf::RenderWindow &window) {
    for (sf::RectangleShape &rect : boxes)
        window.draw(rect);
    for (sf::Text &text : textFields)
        window.draw(text);

    window.setSize({800,600});
    window.setView(sf::View(sf::FloatRect(sf::Vector2f(0, 0),{800,600})));
}

SceneAction LobbyBrowsingScene::handleLeftEvent(sf::Vector2f &mousePos) {
    for (int i = 0; i < boxes.size(); i++) {
        if (boxes[i].getGlobalBounds().contains(mousePos)) {
            // user picked hosts[i]
            std::cout << "Joining: " << hosts[i].ip << ":" << hosts[i].gamePort << std::endl;
            return SceneAction::startGame;  // you'll need to pass host info to game scene
        }
    }
    return SceneAction::None;
}

SceneAction LobbyBrowsingScene::handleRightEvent(sf::Vector2f &mousePos) {
    return SceneAction::None;
}