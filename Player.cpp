#include "Player.hpp"

using namespace std;

Player::Player() {
  name = "";
  money = 5000;
  currentCountry = 0;
  numCountriesVisited = 0;
}

Player::Player(string name) {
  this->name = name;
  money = 5000;
  currentCountry = 0;
  numCountriesVisited = 0;
}

string Player::getName() {
  return name;
}

int Player::getMoney() {
  return money;
}

CountryNode* Player::getCurrentCountry() {
  return currentCountry;
}

int Player::getNumCountriesVisited() {
  return numCountriesVisited;
}

void Player::setName(string name) {
  this->name = name;
}

void Player::setMoney(int money) {
  this->money = money;
}

void Player::setCurrentCountry(CountryNode* country) {
  currentCountry = country;
}

void Player::setNumCountriesVisited(int numCountries) {
  numCountriesVisited = numCountries;
}
