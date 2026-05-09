#pragma once
#include "menuScene.h"
#include "lobbyhosting.h"

class LobbyCreationScene : public MenuScene{
    private:
        std::unique_ptr<LobbyHosting> ld;
        LobbyInfo& hostingInfo;

        sf::Text infoLabels[3];
        sf::RectangleShape buttons[2];
        sf::Text buttonTexts[2];

        void updateInfoText();

    public:
        LobbyCreationScene(LobbyInfo& g);
        ~LobbyCreationScene();
        void updateNet();

        void draw(sf::RenderWindow& window) override;
        SceneAction handleLeftEvent(sf::Vector2f& mousePos) override;
        SceneAction handleRightEvent(sf::Vector2f& mousePos) override;  

        std::unique_ptr<LobbyHosting> getLobbyHosting(){return std::move(ld);};
};