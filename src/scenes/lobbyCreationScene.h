#pragma once
#include "menuScene.h"
#include "lobbyhosting.h"

class LobbyCreationScene : public MenuScene{
    private:
        std::shared_ptr<LobbyHosting> lh;
        sf::Text infoLabels[3];
        sf::RectangleShape buttons[2];
        sf::Text buttonTexts[2];

        void updateInfoText();

    public:
        LobbyCreationScene(std::shared_ptr<Lobby>);
        ~LobbyCreationScene();
        void updateNet();

        void draw(sf::RenderWindow& window) override;
        SceneAction handleLeftEvent(sf::Vector2f& mousePos) override;
        SceneAction handleRightEvent(sf::Vector2f& mousePos) override;  

        std::shared_ptr<Lobby> getLobbyHosting(){return std::move(lh);};
};