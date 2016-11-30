/*
 * actorconnections.cpp
 * Authors: Bhavna Gupta & Ryan Huang
 *
 */
#include "FFGraph.h"
#include <iostream>
#include <fstream>

using namespace std;

int main (int argc, char* argv[]) {
  cout << "extension" << endl;

  FFGraph ffg = FFGraph();
  ffg.loadFromFile("FFdatasheet.tsv");
 
  ofstream out;
  out.open("outputfile");
  ffg.DJS(25000, out);

  out.close();

}
