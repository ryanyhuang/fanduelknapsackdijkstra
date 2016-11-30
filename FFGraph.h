/*
 * ActorGraph.h
 * Author: Ryan Huang and Bhavna Gupta
 * Date:   November 16, 2016
 *
 * This file is meant to exist as a container for starter code that you can 
 * use to read the input file format defined in movie_casts.tsv.
 */

#ifndef FFGRAPH_H
#define FFGRAPH_H

#include <iostream>
#include <queue>
#include <unordered_set>
#include "FFNode.h"

using namespace std;

/*
 *
 */
class WeightPtrComp {
public:
  bool operator()(pair<int, FFNode*> p1, pair<int,FFNode*> p2) {
    return p1.first > p2.first;
  }
};


class FFGraph {

public:
    // hash map of nodes in graph
    unordered_set < FFNode* > nodes;
    FFNode* start;
    FFNode* end;

    /*
     *  constructor for ActorGraph
     */
    FFGraph(void);

    bool loadFromFile(const char* in_filename);
    
    int DJS(int salary, ofstream& out); 
    
    /*
     * Destructor to delete all nodes in graph
     */ 
    ~FFGraph() {
      for (auto it = nodes.begin(); it != nodes.end(); it++) {
        delete *it;
      }
      delete start;
      delete end;
    }
};


#endif // ACTORGRAPH_H
