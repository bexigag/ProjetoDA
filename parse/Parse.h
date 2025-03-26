//
// Created by gonca on 09/03/2025.
//

#ifndef PARSE_H
#define PARSE_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "../data_structures/Graph.h"
#include "location.h"
#include <limits>

class Parse{
  public:
  /**
* @brief empty constructor of the Parse class
* @return Parse
*/
    Parse(){}

  /**
* @brief Reads the locations provided as input by the
* user in the terminal that must be exactly like this
* sequence: Location,Id,Code,Parking
* @param graph graph of type Location in which the input data
* will be stored
* @return void
*/
    void readLocations(Graph<Location> * graph);

  /**
* @brief Reads the locations provided as input by the
* user in the terminal that must be exactly like this
* sequence: Location1,Location2,Driving,Walking
* @param graph graph of type Location in which the input data
* will be stored
* @return void
*/
    void readDistances(Graph<Location> &graph);

  /**
* @brief outputs the graph you provided in the terminal
* Time complexity: O(VE)
* @param graph graph of type Location
*
*
* @return void
*/
    void displayGraph(Graph<Location> &graph);

  /**
* @brief reads the input provided by the user
* in the terminal
* @param mode string that indicates the mode
* of the path (driving or driving-walking)
* @param source int Id of the source node
* @param dest int Id of the destination node
* @param maxWalkTime int max time of walking permitted
* @param includeNode int id of the node that must
* be included in the path
* @param avoidNodes vector<int> that has the Ids of
* the nodes that can't be present in the path
* @param avoidSegments vector<pair<int,int>> that has the
* edges that can't appear in the path
* @return void
*/
    void readInput(std::string& mode, int & source, int & dest, int & maxWalkTime, int & includeNode, std::vector<int> &avoidNodes, std::vector<std::pair<int,int>> &avoidSegments);

  /**
* @brief displays on the terminal the input configurations you provided
* @param mode string that indicates the mode
* of the path (driving or driving-walking)
* @param source int Id of the source node
* @param dest int Id of the destination node
* @param maxWalkTime int max time of walking permitted
* @param includeNode int id of the node that must
* be included in the path
* @param avoidNodes vector<int> that has the Ids of
* the nodes that can't be present in the path
* @param avoidSegments vector<pair<int,int>> that has the
* edges that can't appear in the path
* @return void
*/
    void display(std::string& mode,int & source, int & dest, int & maxWalkTime, int & includeNode, std::vector<int> &avoidNodes, std::vector<std::pair<int,int>> &avoidSegments);
};


void Parse::readLocations(Graph<Location> & graph) {
  std::cout << "Enter locations (insert -1 to stop): " << std::endl;
  std::cout << "Location,Id,Code,Parking" << std::endl;

  std::string line;
  std::cin.ignore();
  std::getline(std::cin, line);

  while (line != "-1") {
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

    graph.addVertex(Location(location, id, code,hasparking));
    std::getline(std::cin, line);
  }
}

void Parse::readDistances(Graph<Location> & graph) {
  std::cout << "Enter distances (insert -1 to stop): " << std::endl;
  std::cout << "Location1,Location2,Driving,Walking" << std::endl;

  std::string line;
  //std::cin.ignore();
  std::getline(std::cin, line);

  while (line != "-1") {
    std::stringstream ss(line);
    std::string code1, code2, driving, walking;

    getline(ss, code1, ',');
    getline(ss, code2, ',');
    getline(ss, driving, ',');
    getline(ss, walking, ',');

    if (driving=="X") {
      graph.addBidirectionalEdge(Location(" ",-1,code1,false), Location(" ",-1,code2,false), INF, stoi(walking));
    }
    else graph.addBidirectionalEdge(Location(" ",-1,code1,false), Location(" ",-1,code2,false), stoi(driving), stoi(walking));
    std::getline(std::cin, line);
  }
}


void Parse::readInput(std::string& mode,int & source, int & dest, int & maxWalkTime, int & includeNode, std::vector<int> &avoidNodes, std::vector<std::pair<int,int>> &avoidSegments) {

  std::cout << "Enter input (insert -1 to stop): " << std::endl;
  std::cout << "Mode:driving\nSource:<id>\nDestination:<id>\nAvoidNodes:<id>,<id>,...\nAvoidSegments:(id,id),(id,id),..\nIncludeNode:<id>\nMaxWalkTime:<int>" << std::endl;

  std::string line;
  std::cin.ignore();
  std::getline(std::cin, line);

  while (line != "-1") {
    std::stringstream ss(line);
    std::string key;
    getline(ss, key, ':');

    if (key=="Mode") {
      ss >> mode;
    }
    else if (key == "Source") {
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
        if (!value.empty() && value != " "){
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

void Parse::display(std::string& mode, int & source, int & dest, int & maxWalkTime, int & includeNode, std::vector<int> &avoidNodes,
  std::vector<std::pair<int,int>> &avoidSegments) {
  std::cout << "These are your input configurations: " << std::endl;
  std::cout << "Mode:" << mode << std::endl;
  std::cout << "Source:" << source << std::endl;
  std::cout << "Destination:" << dest << std::endl;
  std::cout << "MaxWalkTime:" << maxWalkTime << std::endl;
  std::cout << "IncludeNode:" << includeNode << std::endl;
  if (avoidNodes.size() == 0) {std::cout << "AvoidNodes:" << "None" << std::endl;}
  else {
    std::cout << "AvoidNodes:";
    for (int i=0;i<avoidNodes.size()-1;i++) {
      std::cout << avoidNodes[i] << ',';
    }
    std::cout << avoidNodes[avoidNodes.size()-1] << std::endl;
  }

  if (avoidSegments.size() == 0) {
    std::cout << "AvoidSegments:" << "None" << std::endl;
  }
  else{
    std::cout << "AvoidSegments:";
    for (int i=0;i<avoidSegments.size()-1;i++) {
      std::cout << "(" << avoidSegments[i].first << ',' << avoidSegments[i].second << "),";
    }
    std::cout << "(" << avoidSegments[avoidSegments.size()-1].first << ",";
    std::cout << avoidSegments[avoidSegments.size()-1].second << ")" << std::endl;
  }



}

void Parse::displayGraph(Graph<Location> &graph) {
  std::cout << "Graph:" << std::endl;
  for (Vertex<Location> *vertex : graph.getVertexSet()) {
    std::cout << vertex->getInfo().getName()
    << ","<< vertex->getInfo().getId() << ","<< vertex->getInfo().getCode()
    << ","<< vertex->getInfo().getHasParking()<< std::endl;

    std::cout << "Paths: " << std::endl;
    for (Edge<Location> *e: vertex->getAdj()) {
      if (e->getWeightD()==INF){
        std::cout << e->getDest()->getInfo().getName() << ":" <<
        "(no driving) " << e->getWeightW() << "W" << std::endl;
      }
      else {
        std::cout << e->getDest()->getInfo().getName() << ":" <<
        e->getWeightD() << "D " << e->getWeightW() << "W" << std::endl;
      }
    }
  }
}

#endif //PARSE_H
