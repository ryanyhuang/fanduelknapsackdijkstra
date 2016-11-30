#ifndef FFNODE_H
#define FFNODE_H
#include <iostream>

using namespace std;

class FFNode {

public:
  string name;
  int dist;
  int costDist;

  int cost;
  int proj;
  FFNode* prev;
  bool done;

  vector< FFNode* > adjList;

  FFNode(string name, int cost, int pj) : 
    name(name), dist(-1), costDist(0), prev(0), done(false), cost(cost) {
    proj = 30-pj;
  }

  void connectActor (FFNode * teammate) {
    adjList.push_back (teammate);
  }

  void printPlayer(){
    cout << name << ", ";
  }

};
#endif
