#include "Player.hpp"

using namespace std;

Player::Player() {
  name = "";
  money = 5000;
}

Player::Player(string name) {
  this->name = name;
  money = 5000;
}

string Player::getName() {
  return name;
}

int Player::getMoney() {
  return money;
}

void Player::setName(string name) {
  this->name = name;
}

void Player::setMoney(int money) {
  this->money = money;
}
