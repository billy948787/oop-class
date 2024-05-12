#ifndef GAME_H
#define GAME_H

class Game {
 public:
  static Game& getInstance();

  void start();

 private:
  Game();
  static Game* _instance;


};

#endif