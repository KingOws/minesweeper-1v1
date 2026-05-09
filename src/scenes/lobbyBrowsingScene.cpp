#include "lobbybrowsingscene.h"
#include <iostream>

LobbyBrowsingScene::LobbyBrowsingScene(LobbyInfo& g) : joiningInfo(g), infoLabels{sf::Text(font),sf::Text(font),sf::Text(font)}, buttonTexts{sf::Text(font)} {
    joiningInfo.hosting = false;
    // Info label
    float posx = 100, posy = 50;
    for (auto& text : infoLabels) {
        text.setFont(font);
        text.setCharacterSize(28);
        text.setFillColor(sf::Color::Black);
        text.setPosition({posx, posy});
        posy += 45;
    }

    // Buttons (Start, Cancel)
    float bposy = 230;
    std::vector<std::string> buttonLabels = {"Disconnect"};
    for (int i = 0; i < 1; i++) {
        sf::RectangleShape rect;
        sf::Text text(font, buttonLabels[i], 36);

        rect.setSize({600, 100});
        rect.setFillColor({75, 175, 75, 75});
        rect.setPosition({100, bposy});
        bposy += 150;

        text.setFillColor(sf::Color::Black);

        sf::FloatRect tb = text.getLocalBounds();
        text.setOrigin({tb.position.x + tb.size.x / 2.f,
                        tb.position.y + tb.size.y / 2.f});
        text.setPosition({rect.getPosition().x + rect.getSize().x / 2.f,
                          rect.getPosition().y + rect.getSize().y / 2.f});

        buttons[i] = rect;
        buttonTexts[i] = text;
    }

    updateInfoText();
}

void LobbyBrowsingScene::updateInfoText() {
    auto fmt = [](const std::string& label, auto val) {
        std::ostringstream ss;
        ss << label << val;
        return ss.str();
    };

    infoLabels[0].setString(fmt("Player ID:        ", joiningInfo.playerId == -1 ? "N/A" : std::to_string(joiningInfo.playerId)));
    infoLabels[1].setString(fmt("Players:          ", std::to_string(joiningInfo.currentPlayers) + " / " + std::to_string(joiningInfo.maxPlayers)));
    infoLabels[2].setString(fmt("Status:           ", joiningInfo.inGame ? "In Game" : joiningInfo.gameCreated ? "Ready" : "Waiting..."));
}


LobbyBrowsingScene::~LobbyBrowsingScene() {}


void LobbyBrowsingScene::draw(sf::RenderWindow &window) {
    updateInfoText();

    for (auto& text : infoLabels)
        window.draw(text);

    for (auto& rect : buttons)
        window.draw(rect);

    for (auto& text : buttonTexts)
        window.draw(text);
}

SceneAction LobbyBrowsingScene::handleLeftEvent(sf::Vector2f &mousePos) {
    if (buttons[0].getGlobalBounds().contains(mousePos)) {
        if (ld) ld->disconnect();
        return SceneAction::goToMainMenu;
    }
    return SceneAction::None;
}

SceneAction LobbyBrowsingScene::handleRightEvent(sf::Vector2f &mousePos) {
    return SceneAction::None;
}

void LobbyBrowsingScene::update(){    
    
}