#include "lobbycreationScene.h"
#include <iostream>
#include <sstream>

LobbyCreationScene::LobbyCreationScene(std::shared_ptr<Lobby> net) : MenuScene(), infoLabels{sf::Text(font),sf::Text(font),sf::Text(font)}, buttonTexts{sf::Text(font),sf::Text(font)} {
    lh = std::dynamic_pointer_cast<LobbyHosting>(net);
    // Info labels

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
    std::vector<std::string> buttonLabels = {"Start Game", "Cancel"};
    for (int i = 0; i < 2; i++) {
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

void LobbyCreationScene::updateInfoText() {
    auto fmt = [](const std::string& label, auto val) {
        std::ostringstream ss;
        ss << label << val;
        return ss.str();
    };

    infoLabels[0].setString(fmt("Player ID:        ", lh->readPlayerAction().playerId == -1 ? "N/A" : std::to_string(lh->readPlayerAction().playerId)));
    infoLabels[1].setString(fmt("Players:          ", std::to_string(lh->readLobbyInfo().currentPlayers) + " / " + std::to_string(lh->readLobbyInfo().maxPlayers)));
    infoLabels[2].setString(fmt("Status:           ", lh->readPlayerAction().inGame ? "In Game" : lh->readPlayerAction().inGame ? "Ready" : "Waiting..."));
}

void LobbyCreationScene::draw(sf::RenderWindow& window) {
    updateInfoText();

    for (auto& text : infoLabels)
        window.draw(text);

    for (auto& rect : buttons)
        window.draw(rect);

    for (auto& text : buttonTexts)
        window.draw(text);
}

SceneAction LobbyCreationScene::handleLeftEvent(sf::Vector2f& mousePos) {
    if (buttons[0].getGlobalBounds().contains(mousePos))
        return SceneAction::goToMenu;
    else if (buttons[1].getGlobalBounds().contains(mousePos)) {
        if (lh) lh->shutdown();
        return SceneAction::goToMainMenu;
    }
    return SceneAction::None;
}

SceneAction LobbyCreationScene::handleRightEvent(sf::Vector2f& mousePos) {
    return SceneAction::None;
}

LobbyCreationScene::~LobbyCreationScene() = default;