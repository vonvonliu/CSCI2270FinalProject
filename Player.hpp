#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
using namespace std;

class Player {
private:
  string name;
  int money;
public:
  Player();
  Player(string);
  string getName();
  int getMoney();
  void setName(string);
  void setMoney(int);
};
#endif
