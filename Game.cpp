#include "Game.hpp"
#include <iostream>
#include <fstream>

using namespace std;

Game::Game():hashTable(23) {
  player = Player();
  currentCountry = 0;
}

void Game::setup() {
  //display introduction
  ifstream file_stream(".\\Texts\\Introduction.txt");

  if(file_stream.is_open()) {
    string line;
    while(getline(file_stream, line)) {
      cout << line << endl;
    }
  } else
    cout << "Cannot display introduction" << endl;
  cout << endl << endl << endl;

  //ask for player's name
  file_stream.open(".\\Texts\\PlayerName.txt");

  if(file_stream.is_open()) {
    string line;
    while(getline(file_stream, line)) {
      cout << line << endl;
    }
    string name;
    getline(cin, name);
    player.setName(name);
  } else
    cout << "Cannot ask Player for name" << endl;
  cout << endl << endl << endl;

  //load all the countries
  hashTable.addCountriesFromFile(".\\Texts\\CountryInfo.txt");

  //ask for the starting country of the game
  file_stream.open(".\\Texts\\StartCountry.txt");

  if(file_stream.is_open()) {
    string line;
    while(getline(file_stream, line)) {
      cout << line << endl;
    }
    string name;
    //continues to ask player for a valid country name if invalid
    do {
      getline(cin, name);
      if(!hashTable.validStartingCountry(name))  //true if country name is not valid
        cout << "Please enter a valid country name...";
    } while(!hashTable.validStartingCountry(name));

    currentCountry = hashTable.getCountry(name);  //sets current country to what the player chooses

  } else
    cout << "Cannot ask Player for starting country" << endl;
  cout << endl << endl << endl;
}

void Game::game() {
  setup();
  while(currentCountry->name != "Mal Dives") {
    //execute tasks and quizes for each country
  }
}
