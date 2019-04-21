#include "HashTable.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

HashTable::HashTable(int size) {
  hashTableSize = size;
  countries = new CountryNode*[hashTableSize];
  for(int i = 0; i < hashTableSize; i ++)
    countries[i] = 0;
}

HashTable::~HashTable() {
  delete[] countries;
}

unsigned int HashTable::getHash(string name) {
  unsigned int hashValue = 5381;
  int length = name.length();

  for (int i=0;i<length;i++)
    hashValue=((hashValue<<5)+hashValue) + name[i];

  hashValue %= hashTableSize;
  return hashValue;
}

CountryNode* HashTable::getCountry(string name) {
  int hash = getHash(name);
  CountryNode* temp = countries[hash];
  do {
    if(temp->info.at("name") == name)
      return temp;
    temp = temp->next;
  } while(temp != 0);
  //return NULL if country with given name cannot be found
  return 0;
}

void HashTable::insertCountry(CountryNode *country) {
  int hash = getHash(country->info.at("name"));
  //handle collision by chaining
  if(countries[hash] == 0)
    countries[hash] = country;
  else {
    CountryNode* temp = countries[hash];
    while(temp->next != 0) {
      temp = temp->next;
    }
    temp->next = country;
  }
}

void HashTable::insertTasks(CountryNode *country) {
  string file_name = country->info.at("name") + "Tasks";
  ifstream file_stream(file_name);
  if(file_stream.is_open()) {
    string line = "";
    //read in task
    while(getline(file_stream, line)) {
      Task task = Task();
      task.task = line;

      //answer to task
      getline(file_stream, line);
      task.answer = line;

      //answer to task
      getline(file_stream, line);
      task.end = line;

      task.pass = false;
      country->tasks.push(task);
    }
    file_stream.close();
  } else
    cout << "Cannot insert tasks for " << country->info.at("name") << endl;
  cout << endl;
}

void HashTable::addCountriesFromFile(string file_name) {
  ifstream file_stream(file_name);
  if(file_stream.is_open()) {
    string line;
    while(getline(file_stream, line)) {
      string name;
      string capital;
      string population;
      string density;
      string language;
      string ethnicity;
      string religion;
      string currency;
      vector<string> adjacent;
      //read-in
      stringstream string_stream(line); //stringstream to input country info
      getline(string_stream, name, ',');
      getline(string_stream, capital, ',');
      getline(string_stream, population, ',');
      getline(string_stream, density, ',');
      getline(string_stream, language, ',');
      getline(string_stream, ethnicity, ',');
      getline(string_stream, religion, ',');
      getline(string_stream, currency, ',');

      //vector to store adjacent countries
      getline(file_stream, line); //read in line representing the adjacency list
      stringstream string_stream1(line);  //stringstream to input adjacent countries
      string adj;

      while(getline(string_stream1, adj, ',')) {
        adjacent.push_back(adj);
      }

      //insert CountryNode into hashTable;
      CountryNode *country = new struct CountryNode();
      country->info.at("name") = name;
      country->info.at("capital") = capital;
      country->info.at("population") = population;
      country->info.at("density") = density;
      country->info.at("language") = language;
      country->info.at("ethnicity") = ethnicity;
      country->info.at("religion") = religion;
      country->info.at("currency") = currency;
      country->adjacent = adjacent;

      insertCountry(country);
      insertTasks(country);
    }
    file_stream.close();
  } else {
    cout << "Cannot add countries from file" << endl;
  }
}

bool HashTable::isVisited(string name) {
  int hash = getHash(name);
  CountryNode* temp = countries[hash];
  do {
    if(temp->info.at("name") == name)
      return temp->visited;
    temp = temp->next;
  } while(temp != 0);
  cout << "Coutry " << name << " does not exist in Asia." << endl;
  return false;
}

bool HashTable::validStartingCountry(string name) {
  int hash = getHash(name);
  //return true if there exists a country with a corresponding name
  CountryNode* temp = countries[hash];
  do {
    if(temp->info.at("name") == name)
      return true;
    temp = temp->next;
  } while(temp != 0);

  return false;
}

void HashTable::skipTask(string name) {
  CountryNode* country = getCountry(name);

  if(country != 0) {
    Task task = country->tasks.front();
    country->tasks.pop();
    country->tasks.push(task);
  }
}

void HashTable::displayCountries() {
  int count = 1;

  for(int i = 0; i < hashTableSize; i ++) {
    CountryNode* temp = countries[i];
    while(temp != 0) {
      cout << count << ". " << temp->info.at("name") << endl;
      temp = temp->next;
      count ++;
    }
  }
}

void HashTable::displayInformation(CountryNode* country) {
  //display information of given country
  for(auto info = country->info.begin(); info != country->info.end(); ++info) {
    cout << info->first << ": " << info->second << endl;
  }
  cout << endl;
}

void HashTable::performTask(CountryNode* country) {
  while(!country->tasks.front().pass) { //while player has not passed the current task
    
  }
}

void HashTable::tasks(CountryNode* country) {
  cout << "You have a number of tasks to complete before moving onto the next country..." << endl;
  cout << "Let's begin!" << endl;
  while(!country->tasks.empty() {
    performTask(country);
  }
}
