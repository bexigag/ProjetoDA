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

      void resetGraph(Graph<Location> & graph);
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

void Algorithm::algorithm2_1(Graph<Location> & graph, const int& source, const int& dest) {
  Vertex<Location> *src = graph.findVertex(Location("",source,"nullptr",false));

  Vertex<Location> *dst1 = graph.findVertex(Location("",dest,"nullptr",false));
  Vertex<Location> *dst = dst1;


  std::cout << "BestDrivingRoute:";

  distra(graph,src,dst,0);

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
  distra(graph,src,dst,0);
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

}

void Algorithm::algorithm2_2(Graph<Location> & graph, const int& source, const int& dest, const int& includeNode, const std::vector<int>& avoidNodes, const std::vector<std::pair<int,int>> &avoidSegments) {
  Vertex<Location> *src = graph.findVertex(Location("",source,"nullptr",false));
  Vertex<Location> *dst = graph.findVertex(Location("",dest,"nullptr",false));

  for (int id: avoidNodes) {
    graph.findVertex(Location("",id,"nullptr",false))->setProcessing(true);
  }
  for (std::pair a: avoidSegments) {
    Vertex<Location> *v = graph.findVertex(Location("",a.first,"nullptr",false));
    for (Edge<Location> *e: v->getAdj()) {
      Vertex<Location> *w = e->getDest();
      if (w->getInfo().getId() == a.second) {
        e->setSelected(true);
        break;
      }
    }
  }

  std::cout << "RestrictedDrivingRoute:";

  int distance = 0;
  std::stack<int> path;
  Vertex<Location> *secondSrc = src;

  if (includeNode != -1) {
    Vertex<Location> *firstDst = graph.findVertex(Location("",includeNode,"nullptr",false));
    secondSrc = firstDst;
    distra(graph,src,dst,0);
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

  distra(graph,secondSrc,dst,0);

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
}

void Algorithm::algorithm3_1(Graph<Location> & graph, const int& source, const int& dest,const std::vector<int>& avoidNodes, const std::vector<std::pair<int,int>> &avoidSegments,const int & maxWalkTIme) {
  Vertex<Location> *src = graph.findVertex(Location("",source,"nullptr",false));
  Vertex<Location> *dst = graph.findVertex(Location("",dest,"nullptr",false));

  for (int id: avoidNodes) {
    graph.findVertex(Location("",id,"nullptr",false))->setProcessing(true);
  }
  for (std::pair a: avoidSegments) {
    Vertex<Location> *v = graph.findVertex(Location("",a.first,"nullptr",false));
    for (Edge<Location> *e: v->getAdj()) {
      Vertex<Location> *w = e->getDest();
      if (w->getInfo().getId() == a.second) {
        e->setSelected(true);
        break;
      }
    }
  }

  distra(graph,src,nullptr,0);       //driving
  distra(graph,dst,nullptr,1);   //walking

  Vertex<Location> *best = nullptr;
  int bestDistance = INF;
  for (Vertex<Location> *v: graph.getVertexSet()) {
    if (v->getInfo().getHasParking()) {
      if (v->getInfo().getDistW() > maxWalkTIme) continue;
      if (bestDistance > v->getInfo().getDistD() + v->getInfo().getDistW()) {
        bestDistance = v->getInfo().getDistD() + v->getInfo().getDistW();
        best = v;
      }
    }
  }

  std::cout << "DrivingRoute:";
  std::queue<int> pathD = best->getInfo().getPathD();
  while (pathD.size() > 1) {
    std::cout << pathD.front() << ",";
    pathD.pop();
  }
  std::cout << pathD.front() << "(" << best->getInfo().getDistD() << ")" << std::endl;
  pathD.pop();
  std::cout << "ParkingNode:";
  std::cout << best->getInfo().getId() << std::endl;

  std::cout << "WalkingRoute:";
  std::stack<int> pathW = best->getInfo().getPathW();
  while (pathW.size() > 1) {
    std::cout << pathW.top() << ",";
    pathW.pop();
  }
  std::cout << pathW.top()<< "(" << best->getInfo().getDistW() << ")" << std::endl;
  pathW.pop();
  std::cout << "TotalTime:" << bestDistance << std::endl;

}

void Algorithm::distra(Graph<Location> & graph, Vertex<Location> *src,Vertex<Location> *dst ,const int d_w){
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

      v->getInfo().addId(v->getInfo().getId(),d_w);
      v->getInfo().setDist(v->getDist(), d_w);

      v->setVisited(true);
      if (v == dst) break;
      for (Edge<Location> *e : v->getAdj()){
        Vertex<Location> *u = e->getDest();
        if (u->isProcessing() || e->isSelected()) continue;
        if (d_w == 0) {
          if (!u->isVisited() && e->getWeightD() + v->getDist() < u->getDist()){
            u->setDist(v->getDist() + e->getWeightD());
            u->getInfo().copyPathD(v->getInfo().getPathD());
            pq.decreaseKey(u);
          }
        }
        else {
          if (!u->isVisited() && e->getWeightW() + v->getDist() < u->getDist()){
            u->setDist(v->getDist() + e->getWeightW());
            u->getInfo().copyPathW(v->getInfo().getPathW());
            pq.decreaseKey(u);
          }
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
