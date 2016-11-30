/*
 * ActorGraph.cpp
 * Author: Christine Alvarado and Bhavna Gupta and Ryan Huang
 * Date:   November 16, 2016
 *
 * This file is meant to exist as a container for starter code that you can 
 * use to read the input file format defined in movie_casts.tsv.
 */
 
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "FFGraph.h"
#include <queue>
#define WEIGHT(year) (1+(2015-year))
using namespace std;


/*
 * Constructor for ActorGraph
 */
FFGraph::FFGraph(void) {}


/** 
 *
 * Load the graph from a tab-delimited file of actor->movie relationships
 * and create the graph of ActorNodes
 *
 * in_filename - input filename
 * use_weighted_edges - if true, compute edge weights as 1 + 
 * (2015 - movie_year), otherwise all edge weights will be 1
 *
 * return true if file was loaded sucessfully, false otherwise
 */
bool FFGraph::loadFromFile(const char* in_filename) {

    // Initialize the file stream
    ifstream infile(in_filename);

    bool have_header = false;

    vector<FFNode*> QBs;
    vector<FFNode*> RBs;
    vector<FFNode*> WRs;
  
    // keep reading lines until the end of file is reached
    while (infile) {
        string s;
    
        // get the next line
        if (!getline( infile, s )) break;

        if (!have_header) {
            // skip the header
            have_header = true;
            continue;
        }

        istringstream ss( s );
        vector <string> record;

        while (ss) {
            string next;
      
            //get next string before hitting a tab char and put it in 'next'
            if (!getline( ss, next, '\t' )) break;

            record.push_back( next );
        }
    
        if (record.size() != 4) {
            // we should have exactly 3 columns
            continue;
        }

        string name(record[0]);
        string pos(record[1]);
        int cost = stoi(record[2]);
        int proj = stoi(record[3]);

        FFNode* newPlayer = new FFNode(name, cost, proj);
        nodes.insert(newPlayer);

        //cout << "player and proj: " << name << "|" << proj << endl;

        if(pos == "QB") QBs.push_back(newPlayer);
        if(pos == "RB") RBs.push_back(newPlayer);
        if(pos == "WR") WRs.push_back(newPlayer);

     
    }

    //start node
    start = new FFNode("start", 0, 0);
    end = new FFNode("end", 0, 0);

    //cost will default to 30 becuase of how i did it
    end->proj = 0;
    //connect QBs to start
    for(auto it = QBs.begin(); it != QBs.end(); it++){
      start->connectActor(*it);
    }

    //connect RBs to QBs
    for(auto it = QBs.begin(); it != QBs.end(); it++){
      for(auto it2 = RBs.begin(); it2 != RBs.end(); it2++){
        (*it)->connectActor(*it2);
      }
    }

    //connect WRs to RBs
    for(auto it = RBs.begin(); it != RBs.end(); it++){
      for(auto it2 = WRs.begin(); it2 != WRs.end(); it2++){
        (*it)->connectActor(*it2);
      }
    }

    for(auto it = WRs.begin(); it != WRs.end(); it++){
      (*it)->connectActor(end);
    }

/*
    for(auto it = nodes.begin(); it != nodes.end(); it++){
      cout << "adjlist for: " << (*it)->name << endl;
      vector<FFNode*> adjs = (*it)->adjList;

      for(auto it2 = adjs.begin(); it2 != adjs.end(); it2++){
        cout << (*it2)->name << ", ";
      }
      cout << endl;
    }
*/
    // errors reading input file
    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    infile.close();

    return true;
}

int FFGraph::DJS(int salary, ofstream& out){
  
  priority_queue< pair<int, FFNode*>, vector< pair<int, FFNode*> >,
    WeightPtrComp > unsearched;

  FFNode* startPlayer = start;
  startPlayer->dist = 0;

  unsearched.push(make_pair(0, startPlayer));

  while(!unsearched.empty()){
    pair<int, FFNode*> curr = unsearched.top();
    unsearched.pop();

    if(curr.second->name == "end"){
      cout << "team found!" << endl << endl;

      FFNode * working = curr.second;
     
      cout << "total cost: " << working->costDist << endl;
      cout << "total proj: " << (90-working->dist) << endl << endl;
      string output = "";
      while(working->prev->name != "start"){
        output = working->prev->name + "|" + to_string(working->prev->cost)
          + "|" + to_string(30-working->prev->proj) + "\n" + output;
        //cout << working->prev->dist<<endl;
        //cout << working->prev->costDist<<endl;
        working = working->prev;

      }
      cout << output << endl;

    }

    if(!curr.second->done){
      curr.second->done = true;

      auto it = curr.second->adjList.begin();
      for(; it != curr.second->adjList.end(); it++){
        int currWeight = curr.second->dist + (*it)->proj;
        int currCostDist = curr.second->costDist + (*it)->cost;

        //knapsack addition
        if(currCostDist > salary) continue;

        if(currWeight < (*it)->dist || (*it)->dist == -1){
          (*it)->prev = curr.second;
          (*it)->costDist = curr.second->cost + (*it)->cost;
          (*it)->dist = currWeight;
          (*it)->costDist = currCostDist;
          unsearched.push(make_pair(currWeight, (*it)));

        }

      }

    }

  }

}
