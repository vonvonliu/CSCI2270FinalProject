#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <string>
#include <queue>
#include <vector>
#include <unordered_map>

using namespace std;

struct Task {
  bool pass;
  string task;
  string answer;
  string end;
};

// a struct to store country information
struct CountryNode
{
  unordered_map<string, string> info = {
    {"religion",""},
    {"ethnicity",""},
    {"language",""},
    {"density",""},
    {"population",""},
    {"currency",""},
    {"capital",""},
    {"name",""}
  };

  vector<string> adjacent;
  queue<Task> tasks;

  bool visited;

  CountryNode* next;

  CountryNode() {
    next = 0;
    visited = false;
  }
};

class HashTable {
  private:
    CountryNode* *countries;
    int hashTableSize;
    unsigned int getHash(string);
    void insertCountry(CountryNode*);
    void insertTasks(CountryNode*);
    void performTask(CountryNode*);
  public:
    HashTable(int);
    ~HashTable();
    void addCountriesFromFile(string);
    CountryNode* getCountry(string);
    bool isVisited(string);
    bool validStartingCountry(string);
    void skipTask(string);
    void displayCountries();
    void displayInformation(CountryNode*);
    void tasks(CountryNode*);
};
#endif
