#pragma once
#include "IScene.h"
#include <SFML/Graphics.hpp>

//std
#include <stack>

enum ChangeScenes{
  MAIN_MENU,
  DIFF_SELECT,
  IN_GAME,
  SEARCHING_GAME,
  WAITING_GAME,
  NO_CHANGE,
  GO_BACK
};

enum Difficulty{
  EASY,
  MEDIUM, 
  HARD
};

class SceneManager {
private:
  std::unique_ptr<IScene> currScene;
  std::stack<std::unique_ptr<IScene>> history;

public:
  SceneManager();
  ~SceneManager(){};
  void swapScenes(ChangeScenes sceneChange);
  std::unique_ptr<IScene> createGame();
  void displayScene(sf::RenderWindow& window);
  
  const IScene& getScene() const { return *currScene;}
  void handleEvent(sf::Event&);
};



