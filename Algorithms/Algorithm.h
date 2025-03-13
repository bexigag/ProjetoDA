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
      void distra(Graph<Location> & graph, Vertex<Location> *src);
      void algorithm2_1(Graph<Location> & graph, const int& source, const int& dest);
};

void Algorithm::runAlgorithm(Graph<Location> & graph,const std::string& mode,const int & source,const int & dest,const int & maxWalkTime,const int & includeNode,const std::vector<int> &avoidNodes,const std::vector<std::pair<int,int>> &avoidSegments){
  if (mode == "driving") {
      algorithm2_1(graph,source,dest);

  }
}

void Algorithm::algorithm2_1(Graph<Location> & graph, const int& source, const int& dest) {
  Vertex<Location> *src = graph.findVertex(Location("",source,"nullptr",false));

  Vertex<Location> *dst1 = graph.findVertex(Location("",dest,"nullptr",false));
  Vertex<Location> *dst = dst1;

  std::cout << "Source:" << source<<std::endl;
  std::cout << "Destination:"<< dest <<std::endl;
  std::cout << "BestDrivingRoute:";

  distra(graph,src);

  int distance = 0;
  std::stack<int> path;
  path.push(dst->getInfo().getId());
  distance += dst->getPath()->getWeightD();
  dst = dst->getPath()->getOrig();
  while (dst != src){
    Edge<Location> *e = dst->getPath();
    distance += e->getWeightD();
    path.push(dst->getInfo().getId());
    dst->setProcessing(true);
    dst = e->getOrig();
  }
  path.push(src->getInfo().getId());

  while (!path.empty()) {
    std::cout << path.top();
    path.pop();
    if (!path.empty()){std::cout << ",";}
  }
  std::cout<< "(" << distance << ")"<< std::endl;

  std::cout << "AlternativeDrivingRoute:";
  distra(graph,src);
  distance = 0;
  dst = dst1;
  while (dst != src){
    Edge<Location> *e = dst->getPath();
    distance += e->getWeightD();
    path.push(dst->getInfo().getId());
    dst = e->getOrig();
  }

  path.push(src->getInfo().getId());

  while (!path.empty()) {
    std::cout << path.top();
    path.pop();
    if (!path.empty()){std::cout << ",";}
  }
  std::cout<< "(" << distance << ")"<< std::endl;
}

void Algorithm::distra(Graph<Location> & graph, Vertex<Location> *src){
    MutablePriorityQueue<Vertex<Location>> pq;
    for (Vertex<Location> *v :graph.getVertexSet()){
      v->setVisited(false);
      v->setDist(INF);
      v->setPath(nullptr);
    }

    src->setDist(0);

    for (Vertex<Location> *v :graph.getVertexSet()){
      if (v->isProcessing()) {
        v->setVisited(true);
      }
      else pq.insert(v);
    }

    while (!pq.empty()){
      Vertex<Location> *v = pq.extractMin();
      v->setVisited(true);
      for (Edge<Location> *e : v->getAdj()){
        Vertex<Location> *u = e->getDest();
        if (u->isProcessing()) continue;
        if (!u->isVisited() && e->getWeightD() + v->getDist() < u->getDist()){
          u->setDist(v->getDist() + e->getWeightD());
          u->setPath(e);
          pq.decreaseKey(u);
        }
      }
    }
}

#endif //ALGORITHM_H
