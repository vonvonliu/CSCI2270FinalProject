#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "HashTable.hpp"
#include <string>
using namespace std;

class Player {
private:
  string name;
  int money;
  CountryNode* currentCountry;
  int numCountriesVisited;

public:
  Player();
  Player(string);
  string getName();
  int getMoney();
  CountryNode* getCurrentCountry();
  int getNumCountriesVisited();

  void setName(string);
  void setMoney(int);
  void setCurrentCountry(CountryNode*);
  void setNumCountriesVisited(int);
};
#endif
