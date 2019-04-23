#ifndef GAME_HPP
#define GAME_HPP

#include "HashTable.hpp"
#include "Player.hpp"

class Game {
  private:
    HashTable hashTable;
    Player player;

    void setup();
    void turn();
    void end();
  public:
    Game();
    void game();
};
#endif
