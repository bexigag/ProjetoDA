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
      void algorithm2_2(Graph<Location> & graph, const int& source, const int& dest, const int& includeNode, const std::vector<int>& avoidNodes, const std::vector<std::pair<int,int>> &avoidSegments);
      void resetGraph(Graph<Location> & graph);
};

void Algorithm::runAlgorithm(Graph<Location> & graph,const std::string& mode,const int & source,const int & dest,const int & maxWalkTime,const int & includeNode,const std::vector<int> &avoidNodes,const std::vector<std::pair<int,int>> &avoidSegments){
  if (mode == "driving") {
      if (!avoidNodes.empty() || !avoidSegments.empty() ||includeNode != -1) {
        algorithm2_2(graph,source,dest,includeNode,avoidNodes,avoidSegments);
      }
      else algorithm2_1(graph,source,dest);
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

  if (dst->getPath() == nullptr) {
    std::cout << "none" << std::endl;
  }
  else {
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
  }

  dst = dst1;
  std::cout << "AlternativeDrivingRoute:";
  distra(graph,src);
  if (dst->getPath() == nullptr) {
    std::cout << "none" << std::endl;
  }
  else {
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

  resetGraph(graph);
}

void Algorithm::algorithm2_2(Graph<Location> & graph, const int& source, const int& dest, const int& includeNode, const std::vector<int>& avoidNodes, const std::vector<std::pair<int,int>> &avoidSegments) {
  Vertex<Location> *src = graph.findVertex(Location("",source,"nullptr",false));
  Vertex<Location> *dst = graph.findVertex(Location("",dest,"nullptr",false));

  for (int id: avoidNodes) {
    graph.findVertex(Location("",id,"nullptr",false))->setProcessing(true);
  }
  for (std::pair a: avoidSegments) {
    Vertex<Location> *src = graph.findVertex(Location("",a.first,"nullptr",false));
    for (Edge<Location> *e: src->getAdj()) {
      Vertex<Location> *dst = e->getDest();
      if (dst->getInfo().getId() == a.second) {
        e->setSelected(true);
        break;
      }
    }
  }

  std::cout << "Source:" << source<<std::endl;
  std::cout << "Destination:"<< dest <<std::endl;
  std::cout << "RestrictedDrivingRoute:";

  int distance = 0;
  std::stack<int> path;
  Vertex<Location> *secondSrc = src;

  if (includeNode != -1) {
    Vertex<Location> *firstDst = graph.findVertex(Location("",includeNode,"nullptr",false));
    secondSrc = firstDst;
    distra(graph,src);
    if (dst->getPath() == nullptr) {
      std::cout << "none" << std::endl;
    }
    else {
      distance += firstDst->getPath()->getWeightD();
      firstDst = firstDst->getPath()->getOrig();
      while (firstDst != src) {
        Edge<Location> *e = firstDst->getPath();
        distance += e->getWeightD();
        path.push(firstDst->getInfo().getId());
        firstDst = e->getOrig();
      }
      path.push(src->getInfo().getId());

      while (!path.empty()) {
        std::cout << path.top() << ",";
        path.pop();

      }
    }
  }

  distra(graph,secondSrc);

  if (dst->getPath() == nullptr) {
    std::cout << "none" << std::endl;
  }
  else {
    path.push(dst->getInfo().getId());
    distance += dst->getPath()->getWeightD();
    dst = dst->getPath()->getOrig();
    while (dst != secondSrc){
      Edge<Location> *e = dst->getPath();
      distance += e->getWeightD();
      path.push(dst->getInfo().getId());
      dst = e->getOrig();
    }
    path.push(secondSrc->getInfo().getId());

    while (!path.empty()) {
      std::cout << path.top();
      path.pop();
      if (!path.empty()){std::cout << ",";}
    }
    std::cout<< "(" << distance << ")"<< std::endl;
  }
  resetGraph(graph);
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
        if (u->isProcessing() || e->isSelected()) continue;
        if (!u->isVisited() && e->getWeightD() + v->getDist() < u->getDist()){
          u->setDist(v->getDist() + e->getWeightD());
          u->setPath(e);
          pq.decreaseKey(u);
        }
      }
    }
}

void Algorithm::resetGraph(Graph<Location> & graph) {
  for (Vertex<Location> *v :graph.getVertexSet()) {
    v->setProcessing(false);
    for (Edge<Location> *e : v->getAdj()) {
      e->setSelected(false);
    }
  }
}


#endif //ALGORITHM_H
