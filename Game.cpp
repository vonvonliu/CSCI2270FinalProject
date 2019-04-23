#include "Game.hpp"
#include <iostream>
#include <fstream>

using namespace std;

Game::Game():hashTable(23) {
  player = Player();
}

void Game::setup() {
  //display introduction
  ifstream file_stream("Introduction.txt");

  if(file_stream.is_open()) {
    string line;
    while(getline(file_stream, line)) {
      cout << line << endl;
    }
    file_stream.close();
  } else
    cout << "Cannot display introduction" << endl;
  cout << endl;

  //ask for player's name
  file_stream.open("PlayerName.txt");

  if(file_stream.is_open()) {
    string line;
    while(getline(file_stream, line)) {
      cout << line << endl;
    }
    file_stream.close();
    string name;
    getline(cin, name);
    player.setName(name);
  } else
    cout << "Cannot ask Player for name" << endl;
  cout << endl << endl << endl;

  //load all the countries
  hashTable.addCountriesFromFile("CountryInfo.txt");

  //ask for the starting country of the game
  file_stream.open("StartCountry.txt");

  if(file_stream.is_open()) {
    string line;
    while(getline(file_stream, line)) {
      cout << line << endl;
    }
    hashTable.displayCountries(); //display list of countries for user to choose from
    cout << endl;

    file_stream.close();
    string name;
    //continues to ask player for a valid country name if invalid
    do {
      getline(cin, name);
      if(!hashTable.validStartingCountry(name))  //true if country name is not valid
        cout << "Please enter a valid country name...";
    } while(!hashTable.validStartingCountry(name));

    player.setCurrentCountry(hashTable.getCountry(name)); //sets current country to what the player chooses

  } else
    cout << "Cannot ask Player for starting country" << endl;
  cout << endl << endl << endl;
}

void Game::turn() {
  cout << "You have arrived at " << player.getCurrentCountry()->info.at("Name") << endl;  //display current country

  hashTable.displayInformation(player.getCurrentCountry());

  hashTable.tasks(player.getCurrentCountry());  //tasks

  hashTable.quizes(player.getCurrentCountry()); //quiz (where country is set to visited)

  player.setNumCountriesVisited(player.getNumCountriesVisited() + 1);  //increment number of countries visited

  //move on to next country
  player.setCurrentCountry(hashTable.nextCountry(player.getCurrentCountry()));
}

void Game::game() {
  setup();
  //player has not traveled to all of the countries
  while(player.getNumCountriesVisited() < 23) {
    //execute tasks and quizes for each country
    turn();
  }
  cout << "You see " << endl;
}
