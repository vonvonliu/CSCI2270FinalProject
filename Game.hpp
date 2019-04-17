#ifndef GAME_HPP
#define GAME_HPP

#include "HashTable.hpp"
#include "Player.hpp"

class Game {
  private:
    HashTable hashTable;
    Player player;
    CountryNode* currentCountry;
    
    void setup();
  public:
    Game();
    void game();
};
#endif
