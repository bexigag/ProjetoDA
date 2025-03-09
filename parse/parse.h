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

template <class T>
class parse{
  public:
    parse(std::string filename): filename(filename){}
    void readLocations(Graph<T> &graph);
    void readDistances(Graph<T> &graph);
  private:
    std::string filename;
};

template <class T>
void parse<T>::readLocations(Graph<T>& graph) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error opening file " << filename << std::endl;
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
void parse<T>::readDistances(Graph<T>& graph) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error opening file " << filename << std::endl;
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

    graph.addEdge(code1, code2);
  }
}



#endif //PARSE_H
