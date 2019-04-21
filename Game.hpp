#ifndef GAME_HPP
#define GAME_HPP

#include "HashTable.hpp"
#include "Player.hpp"

class Game {
  private:
    HashTable hashTable;
    Player player;
    string clues[22];

    void setup();
    void turn();
    void displayClue();
  public:
    Game();
    void game();
};
#endif
