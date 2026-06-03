#pragma once
#include "../net/NetworkInfo.h"
#include "../scenes/IScene.h"
#include "spritemanager.h"
#include <SFML/Graphics.hpp>

//std
#include <stack>

enum class GAMESTATE;

enum class SceneAction{
  MAIN_MENU,
  DIFF_SELECT,
  IN_GAME,
  SEARCHING_GAME,
  WAITING_GAME,
  NO_CHANGE,
  GO_BACK
};

enum class Difficulty{
  EASY,
  MEDIUM, 
  HARD
};

class SceneManager {
private:
  std::unique_ptr<IScene> currScene;
  std::stack<std::unique_ptr<IScene>> history;
  SpriteManager spriteManager{1};
  void swapScenes(SceneAction sceneChange);
  std::unique_ptr<IScene> createGame();

public:
  SceneManager();
  ~SceneManager(){};
  void update();
  void update(NetworkInfo& networkInfo);

  void displayScene(sf::RenderWindow& window);
  const IScene& getScene() const { return *currScene;}
  void handleEvent(sf::Event&, GAMESTATE& gameState);
};



