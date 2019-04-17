#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <string>
#include <queue>
#include <vector>

using namespace std;

struct Task {
  bool pass;
  string task;
};

// a struct to store country information
struct CountryNode
{
  string name;

  string capital;
  string population;
  string density;
  string language;
  string ethnicity;
  string religion;
  string currency;

  vector<string> adjacent;
  queue<Task> tasks;

  bool visited;

   CountryNode() {

   }

  CountryNode(string nam, string cap, string pop, string den, string lan, string eth, string rel, string cur, vector<string> adj) {
    name = nam;
    capital = cap;
    population = pop;
    density = den;
    language = lan;
    currency = cur;
    ethnicity = eth;
    religion = rel;
    adjacent = adj;
    visited = false;
  }
};

class HashTable {
  private:
    CountryNode *countries;
    int hashTableSize;
    unsigned int getHash(string);
    void insertCountry(CountryNode*);
    void insertTasks(CountryNode*);
  public:
    HashTable(int);
    ~HashTable();
    void addCountriesFromFile(string);
    CountryNode* getCountry(string);
    bool isVisited(string);
    bool validStartingCountry(string);
    void skipTask(string);
};
#endif
