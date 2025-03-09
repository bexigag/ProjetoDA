//
// Created by gonca on 09/03/2025.
//

#ifndef PARSE_H
#define PARSE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include "../data_structures/Graph.h"
#include "location.h"
#include <limits>

template <class T>
class Parse{
  public:
    Parse(){}
    void readLocations(Graph<T> &graph);
    void readDistances(Graph<T> &graph);
    void readInput(std::string filename);

};

template <class T>
void Parse<T>::readLocations(Graph<T>& graph) {
  std::ifstream file("../DataSet/Locations.csv");
  if (!file.is_open()) {
    std::cerr << "Error opening file Locations.csv" << std::endl;
    return;
  }

  std::string line;
  getline(file, line);

  while (getline(file, line)) {
    std::stringstream ss(line);
    std::string location, idstr, code, parking;

    getline(ss, location, ',');
    getline(ss, idstr, ',');
    getline(ss, code, ',');
    getline(ss, parking, ',');

    int id = std::stoi(idstr);
    bool hasparking;
    if (parking == "1") hasparking = true;
    else hasparking = false;

    graph.addVertex(new Location(location, id, code,hasparking));
  }
}

template <class T>
void Parse<T>::readDistances(Graph<T>& graph) {
  std::ifstream file("../DataSet/Distances.csv");
  if (!file.is_open()) {
    std::cerr << "Error opening file Distances.csv" << std::endl;
  }

  std::string line;
  getline(file, line);

  while (getline(file, line)) {
    std::stringstream ss(line);
    std::string code1, code2, driving, walking;

    getline(ss, code1, ',');
    getline(ss, code2, ',');
    getline(ss, walking, ',');
    getline(ss, driving, ',');

    if (driving == "X"){
      graph.addEdge(code1, code2, INF, stoi(walking));
    }
    else graph.addEdge(code1, code2, stoi(driving), stoi(walking));
  }
}



#endif //PARSE_H
