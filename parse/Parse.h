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

class Parse{
  public:
    Parse(){}
    void readLocations(Graph<Location> &graph);
    void readDistances(Graph<Location> &graph);
    void readInput(std::string filename, int & source, int & dest, int & maxWalkTime, int & includeNode, std::vector<int> &avoidNodes, std::vector<std::pair<int,int>> &avoidSegments);

};


void Parse::readLocations(Graph<Location> & graph) {
  std::cout << "Enter locations (insert -1 to stop): " << std::endl;
  std::cout << "Location,Id,Code,Parking" << std::endl;

  std::string line;
  std::cin.ignore();
  std::getline(std::cin, line);

  while (line != "-1") {
    std::cout << line << std::endl;
    std::stringstream ss(line);
    std::string location, idstr, code, parking;

    getline(ss, location, ',');
    getline(ss, idstr, ',');
    getline(ss, code, ',');
    getline(ss, parking, ',');

    std::cout << location << ',' << idstr << ',' << code << ',' << parking << std::endl;

    int id = std::stoi(idstr);
    bool hasparking;
    if (parking == "1") hasparking = true;
    else hasparking = false;

    graph.addVertex(Location(location, id, code,hasparking));
    std::getline(std::cin, line);
  }
}

void Parse::readDistances(Graph<Location> & graph) {
  std::cout << "Enter distances (insert -1 to stop): " << std::endl;
  std::cout << "Location,Id,Code,Parking" << std::endl;

  std::string line;
  std::cin.ignore();
  std::getline(std::cin, line);

  while (line != "-1") {
    std::stringstream ss(line);
    std::string code1, code2, driving, walking;

    getline(ss, code1, ',');
    getline(ss, code2, ',');
    getline(ss, driving, ',');
    getline(ss, walking, ',');


    if (driving == "X"){
      graph.addEdge(Location(" ",-1,code1,false), Location(" ",-1,code2,false), INF, stoi(walking));
    }
    else graph.addEdge(Location(" ",-1,code1,false), Location(" ",-1,code2,false), stoi(driving), stoi(walking));
    std::getline(std::cin, line);
  }
}

void Parse::readInput(std::string filename, int & source, int & dest, int & maxWalkTime, int & includeNode, std::vector<int> &avoidNodes, std::vector<std::pair<int,int>> &avoidSegments) {
  std::cout << "Enter input (insert -1 to stop): " << std::endl;
  std::cout << "Mode:driving\nSource:<id>\nDestination:<id>\nAvoidNodes:<id>,<id>,...\nAvoidSegments:(id,id),(id,id),..\nIncludeNode:<id>\nMaxWalkTime:<int>" << std::endl;

  std::string line;
  std::cin.ignore();
  std::getline(std::cin, line);

  while (line != "-1") {
    std::stringstream ss(line);
    std::string key;
    getline(ss, key, ':');

    if (key == "Source") {
      ss >> source;
    } else if (key == "Destination") {
      ss >> dest;
    } else if (key == "MaxWalkTime") {
      ss >> maxWalkTime;
    } else if (key == "IncludeNode") {
      ss >> includeNode;
    } else if (key == "AvoidNodes") {
      avoidNodes.clear();
      std::string value;
      while (getline(ss, value, ',')) {
        if (!value.empty()) {
          avoidNodes.push_back(stoi(value));
        }
      }
    } else if (key == "AvoidSegments") {
      avoidSegments.clear();
      std::string segment;
      while (getline(ss, segment, ')')) {
        if (segment.empty() || segment == "(") continue;
        size_t start = segment.find('(');
        if (start != std::string::npos) {
          segment = segment.substr(start + 1);  // Remove o '('
        }
        std::stringstream segmentStream(segment);
        std::string loc1, loc2;
        getline(segmentStream, loc1, ',');
        getline(segmentStream, loc2, ',');
        if (!loc1.empty() && !loc2.empty()) {
          avoidSegments.emplace_back(stoi(loc1), stoi(loc2));
        }
      }
    }
    std::getline(std::cin, line);
  }

}


#endif //PARSE_H
