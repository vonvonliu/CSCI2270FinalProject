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

struct Quiz {
  bool pass;
  string quiz;
  string answer;
};

// a struct to store country information
struct CountryNode
{
  unordered_map<string, string> info = {
    {"Main Religion(s)",""},
    {"Dominant Ethnic Groups",""},
    {"Official Language(s)",""},
    {"Density Ranking",""},
    {"Population Ranking",""},
    {"Currency",""},
    {"Capital",""},
    {"Name",""}
  };

  vector<string> adjacent;
  queue<Task> tasks;
  queue<Quiz> quiz;

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
    void insertQuiz(CountryNode*);
    void performTask(CountryNode*);
    void performQuiz(CountryNode*);
    bool correctAnswer(string, string);
    bool validResponse(string);
    bool validAdjacentCountry(string, vector<string>);
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
    void quizes(CountryNode*);
    CountryNode* nextCountry(CountryNode*);
};
#endif
