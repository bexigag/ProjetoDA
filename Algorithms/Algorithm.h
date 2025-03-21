//
// Created by gonca on 13/03/2025.
//

#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <iostream>
#include <vector>
#include "../data_structures/Graph.h"
#include "../parse/Location.h"
#include "../data_structures/MutablePriorityQueue.h"
#include <limits>
#include <stack>

class Algorithm{
    public:
      Algorithm(){}
      void runAlgorithm(Graph<Location> & graph, const std::string& mode,const int & source,const int & dest,const int & maxWalkTime,const int & includeNode,const std::vector<int> &avoidNodes,const std::vector<std::pair<int,int>> &avoidSegments);
    private:
      void distra(Graph<Location> & graph, Vertex<Location> *src,Vertex<Location> *dst , const int d_w);
      void algorithm2_1(Graph<Location> & graph, const int& source, const int& dest); //not restricted
      void algorithm2_2(Graph<Location> & graph, const int& source, const int& dest, const int& includeNode, const std::vector<int>& avoidNodes, const std::vector<std::pair<int,int>> &avoidSegments);
      //restricted
      void algorithm3_1(Graph<Location> & graph, const int& source, const int& dest,const std::vector<int>& avoidNodes, const std::vector<std::pair<int,int>> &avoidSegments,const int & maxWalkTIme);
      void algorithm3_2(Graph<Location> & graph, const int& source, const int& dest,const int & maxWalkTIme);

      void output_path(std::stack<int> & path);
      void resetGraph(Graph<Location> & graph);
      void resetPaths(Graph<Location> & graph);


};

void Algorithm::runAlgorithm(Graph<Location> & graph,const std::string& mode,const int & source,const int & dest,const int & maxWalkTime,const int & includeNode,const std::vector<int> &avoidNodes,const std::vector<std::pair<int,int>> &avoidSegments){
  std::cout << "Source:" << source<<std::endl;
  std::cout << "Destination:"<< dest <<std::endl;
  if (mode == "driving") {
      if (!avoidNodes.empty() || !avoidSegments.empty() ||includeNode != -1) {
        algorithm2_2(graph,source,dest,includeNode,avoidNodes,avoidSegments);
      }
      else algorithm2_1(graph,source,dest);
  }
  else if (mode == "driving-walking") {
    algorithm3_1(graph,source,dest,avoidNodes,avoidSegments,maxWalkTime);
  }
  resetGraph(graph);

}

void Algorithm::resetPaths(Graph<Location> & graph) {
  for (Vertex<Location> *v :graph.getVertexSet()) {
    v->getInfo().setPath(nullptr,2);
  }
}

void Algorithm::resetGraph(Graph<Location> & graph) {
  for (Vertex<Location> *v :graph.getVertexSet()) {
    v->setProcessing(false);
    v->getInfo().setPath(nullptr,2);
    for (Edge<Location> *e : v->getAdj()) {
      e->setSelected(false);
    }
  }
}

void Algorithm::output_path(std::stack<int> & path) {
    while (!path.empty()) {
      std::cout << path.top();
      path.pop();
      if (!path.empty()){std::cout << ",";}
    }
}

#endif //ALGORITHM_H
