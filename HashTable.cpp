#include "HashTable.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

HashTable::HashTable(int size) {
  hashTableSize = size;
  countries = new CountryNode[hashTableSize];
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
  if(countries[hash].name == name)
    return &countries[hash];
  else
    return 0;
}

void HashTable::insertCountry(CountryNode *country) {
  int hash = getHash(country->name);
  countries[hash] = *country;
}

void HashTable::insertTasks(CountryNode *country) {
  string file_name = country->name + "Tasks";
  ifstream file_stream(".\\Texts\\" + file_name);
  if(file_stream.is_open()) {
    string line = "";
    while(getline(file_stream, line)) {
      Task task = Task();
      task.task = line;
      task.pass = false;
      country->tasks.push(task);
    }
  } else
    cout << "Cannot insert tasks for " << country->name << endl;
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
      CountryNode *country = new struct CountryNode(name, capital, population, density, language, ethnicity, religion, currency, adjacent);
      insertCountry(country);
      insertTasks(country);
    }
  } else {
    cout << "Cannot add countries from file" << endl;
  }
}

bool HashTable::isVisited(string name) {
  return countries[getHash(name)].visited;
}

bool HashTable::validStartingCountry(string name) {
  int hash = getHash(name);
  return countries[hash].name == name;
}

void HashTable::skipTask(string name) {
  CountryNode* country = getCountry(name);

  if(country != 0) {
    Task task = country->tasks.front();
    country->tasks.pop();
    country->tasks.push(task);
  }
}
