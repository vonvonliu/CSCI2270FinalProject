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
    if(temp->info.at("Name") == name)
      return temp;
    temp = temp->next;
  } while(temp != 0);
  //return NULL if country with given name cannot be found
  return 0;
}

void HashTable::insertCountry(CountryNode *country) {
  int hash = getHash(country->info.at("Name"));
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
  string file_name = country->info.at("Name") + "Tasks.txt";
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

      //explanation to task
      getline(file_stream, line);
      task.end = line;

      task.pass = false;
      country->tasks.push(task);
    }
    file_stream.close();
  } else
    cout << "Cannot insert tasks for " << country->info.at("Name") << endl << endl;
}

void HashTable::insertQuiz(CountryNode *country) {
  string file_name = country->info.at("Name") + "Quiz.txt";
  ifstream file_stream(file_name);
  if(file_stream.is_open()) {
    string line = "";
    //read in quiz

    while(getline(file_stream, line)) {
      Quiz quiz = Quiz();
      quiz.quiz = line;

      //answer to quiz
      getline(file_stream, line);
      quiz.answer = line;

      quiz.pass = false;
      country->quiz.push(quiz);
    }
    file_stream.close();
  } else
    cout << "Cannot insert quiz for " << country->info.at("Name") << endl << endl;
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
      country->info.at("Name") = name;
      country->info.at("Capital") = capital;
      country->info.at("Population Ranking") = population;
      country->info.at("Density Ranking") = density;
      country->info.at("Official Language(s)") = language;
      country->info.at("Dominant Ethnic Groups") = ethnicity;
      country->info.at("Main Religion(s)") = religion;
      country->info.at("Currency") = currency;
      country->adjacent = adjacent;

      insertCountry(country);
      insertTasks(country);
      insertQuiz(country);
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
    if(temp->info.at("Name") == name)
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
  while(temp != 0) {
    if(temp->info.at("Name") == name)
      return true;
    temp = temp->next;
  }

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

void HashTable::skipQuiz(string name) {
  CountryNode* country = getCountry(name);

  if(country != 0) {
    Quiz quiz = country->quiz.front();
    country->quiz.pop();
    country->quiz.push(quiz);
  }
}

void HashTable::displayCountries() {
  int count = 1;

  for(int i = 0; i < hashTableSize; i ++) {
    CountryNode* temp = countries[i];
    while(temp != 0) {
      cout << count << ". " << temp->info.at("Name") << endl;
      temp = temp->next;
      count ++;
    }
  }
}

void HashTable::displayInformation(CountryNode* country) {
  //display information of given country
  for(auto info = country->info.begin(); info != country->info.end(); info ++) {
    if(info->first != "Name")
      cout << info->first << ": " << info->second << endl;
  }
  cout << endl;
}

bool HashTable::correctAnswer(string playerAnswer, string correctAnswer) {
  if(playerAnswer.length() < 1) {  //player's answer cannot be right
    return false;
  }

  for(int i = 0; i <= correctAnswer.length() - playerAnswer.length(); i ++) {
    if(playerAnswer == correctAnswer.substr(i, playerAnswer.length())) {
      if(correctAnswer[i + playerAnswer.length()] == '/')
        return true;
    }
  }
  return false;
}

bool HashTable::validResponse(string response) {
  return response == "Yes" || response == "yes" || response == "No" || response == "no";
}

void HashTable::performTask(CountryNode* country) {
  string answer;
  bool skipped = false;
  string message = country->tasks.front().end;
  do {
    cout << country->tasks.front().task << endl;  //print out task
    getline(cin, answer);
    if(!correctAnswer(answer, country->tasks.front().answer)) {
      cout << "Wrong answer. Try again...";
      //asks player to skip
      string response;
      do {
        cout << "Or do you want to skip and answer later? (Enter yes/no)" << endl;
        getline(cin, response);
      } while(!validResponse(response));
      if(response == "Yes" || response == "yes") {
        skipped = true;
        skipTask(country->info.at("Name"));
        break;
      }
    }
  } while(!correctAnswer(answer, country->tasks.front().answer));
  if(!skipped) { //print out message to player if player completes task
    cout << message << endl;
    country->tasks.front().pass = true;
    country->tasks.pop();
  }
  cout << endl;
}

void HashTable::performQuiz(CountryNode* country) {
  string answer;
  bool skipped = false;
  string message = "Correct!";
  do {
    cout << country->quiz.front().quiz << endl;  //print out task
    getline(cin, answer);
    if(!correctAnswer(answer, country->quiz.front().answer)) {
      cout << "Wrong answer. Try again...";
      //asks player to skip
      string response;
      do {
        cout << "Or do you want to skip and answer later? (Enter yes/no)" << endl;
        getline(cin, response);
      } while(!validResponse(response));
      if(response == "Yes" || response == "yes") {
        skipped = true;
        skipQuiz(country->info.at("Name"));
        break;
      }
    }
  } while(!correctAnswer(answer, country->quiz.front().answer));
  if(!skipped) { //print out message to player if player completes task
    cout << message << endl;
    country->quiz.front().pass = true;
    country->quiz.pop();
  }
  cout << endl;
}

void HashTable::tasks(CountryNode* country) {
  cout << "You have a number of tasks to complete before moving on to the next country..." << endl;
  cout << "Let's begin!" << endl;
  cout << endl;
  while(!country->tasks.empty()) {
    performTask(country);
  }
  cout << "Unfortunately, Chase is not in " << country->info.at("Name") << endl;
}

void HashTable::quizes(CountryNode* country) {
  cout << "In order to move on to the next country, you must answer correctly a set of quiz questions..." << endl;
  cout << "Let's begin!" << endl;
  cout << endl;
  //asks player quiz questions
  while(!country->quiz.empty()) {
    performQuiz(country);
  }
  country->visited = true;  //set country to visited
}

bool HashTable::validAdjacentCountry(string name, vector<string> adj) {
  for(int i = 0; i < adj.size(); i ++) {
    if(adj[i] == name)
      return true;
  }
  return false;
}

CountryNode* HashTable::nextCountry(CountryNode* country) {
  cout << "Which country would you like to travel to next? (Enter one of the names from the list below)" << endl;
  vector<string> adj;
  int count = 1;
  for(int i = 0; i < country->adjacent.size(); i ++) {
    CountryNode* nextCountry = getCountry(country->adjacent[i]);
    if(nextCountry != 0) {
      if(!nextCountry->visited) {
        cout << count << ". " << nextCountry->info.at("Name") << endl;
        adj.push_back(nextCountry->info.at("Name"));
        count ++;
      }
    }
  }
  //player can no longer move on
  if(adj.size() == 0) {
    cout << "You are trapped and can no longer move on to the next country.\nYou have failed to rescue Chase." << endl;
    return 0;
  }
  string name;
  //continues to ask player for a valid country name if invalid
  do {
    getline(cin, name);
    if(!validStartingCountry(name))  //true if country name is not valid
      cout << "Please enter a valid country name...";
    else if(!validAdjacentCountry(name, adj)) //true if country has been visited
      cout << name << " has already been visited..." << endl;
  } while(!validStartingCountry(name) || !validAdjacentCountry(name, adj));

  return getCountry(name);
}
