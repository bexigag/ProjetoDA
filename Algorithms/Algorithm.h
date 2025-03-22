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

void Algorithm::distra(Graph<Location> & graph, Vertex<Location> *src,Vertex<Location> *dst ,const int d_w){
  MutablePriorityQueue<Vertex<Location>> pq;
  for (Vertex<Location> *v :graph.getVertexSet()){
    v->setVisited(false);
    v->setDist(INF);
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

    v->getInfo().setDist(v->getDist(), d_w);

    v->setVisited(true);
    if (v == dst) break;
    for (Edge<Location> *e : v->getAdj()){
      Vertex<Location> *u = e->getDest();
      if (u->isProcessing() || e->isSelected()) continue;
      if (d_w == 0) {
        if (!u->isVisited() && e->getWeightD() + v->getDist() < u->getDist()){
          u->setDist(v->getDist() + e->getWeightD());
          u->getInfo().setPath(e,d_w);
          pq.decreaseKey(u);
        }
      }
      else {
        if (!u->isVisited() && e->getWeightW() + v->getDist() < u->getDist()){
          u->setDist(v->getDist() + e->getWeightW());
          u->getInfo().setPath(e,d_w);
          pq.decreaseKey(u);
        }
      }

    }
  }
}

#include "Algorithm.h"

void Algorithm::algorithm2_1(Graph<Location> & graph, const int& source, const int& dest) {
    Vertex<Location> *src = graph.findVertex(Location("",source,"nullptr",false));

    Vertex<Location> *dst1 = graph.findVertex(Location("",dest,"nullptr",false));
    Vertex<Location> *dst = dst1;

    std::cout << "BestDrivingRoute:";

    distra(graph,src,dst,0);

    std::stack<int> path;

    if (dst->getInfo().getPathD() == nullptr) {
        std::cout << "none" << std::endl;
    }
    else {
        path.push(dst->getInfo().getId());
        dst = dst->getInfo().getPathD()->getOrig();
        while (dst != src){
            Edge<Location> *e = dst->getInfo().getPathD();
            path.push(dst->getInfo().getId());
            dst->setProcessing(true);
            dst = e->getOrig();
        }
        path.push(src->getInfo().getId());
        output_path(path);
        std::cout<< "(" << dst1->getInfo().getDistD() << ")"<< std::endl;
    }

    dst = dst1;

    std::cout << "AlternativeDrivingRoute:";
    resetPaths(graph);
    distra(graph,src,dst,0);
    if (dst->getInfo().getPathD() == nullptr) {
        std::cout << "none" << std::endl;
    }
    else {
        while (dst != src){
            Edge<Location> *e = dst->getInfo().getPathD();
            path.push(dst->getInfo().getId());
            dst = e->getOrig();
        }
        path.push(src->getInfo().getId());
        output_path(path);
        std::cout<< "(" << dst1->getInfo().getDistD() << ")"<< std::endl;
    }
}


void Algorithm::algorithm2_2(Graph<Location> & graph, const int& source, const int& dest, const int& includeNode, const std::vector<int>& avoidNodes, const std::vector<std::pair<int,int>> &avoidSegments) {
  Vertex<Location> *src = graph.findVertex(Location("",source,"nullptr",false));
  Vertex<Location> *dst = graph.findVertex(Location("",dest,"nullptr",false));

  for (int id: avoidNodes) {
    graph.findVertex(Location("",id,"nullptr",false))->setProcessing(true);
  }
  for (std::pair a: avoidSegments) {
    Vertex<Location> *v1 = graph.findVertex(Location("",a.first,"nullptr",false));
    Vertex<Location> *v2 = graph.findVertex(Location("",a.second,"nullptr",false));
    for (Edge<Location> *e: v1->getAdj()) {
      Vertex<Location> *w = e->getDest();
      if (w->getInfo().getId() == a.second) {
        e->setSelected(true);
        break;
      }
    }
    for (Edge<Location> *e: v2->getAdj()) {
      Vertex<Location> *w = e->getDest();
      if (w->getInfo().getId() == a.first) {
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
    distra(graph,src,firstDst,0);
    distance += firstDst->getInfo().getDistD();
    if (dst->getInfo().getPathD() == nullptr) {
      std::cout << "none" << std::endl;
    }
    else {
      firstDst = firstDst->getInfo().getPathD()->getOrig();
      while (firstDst != src) {
        Edge<Location> *e = firstDst->getInfo().getPathD();
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

  if (dst->getInfo().getPathD() == nullptr) {
    std::cout << "none" << std::endl;
  }
  else {
    distance += dst->getInfo().getDistD();
    while (dst != secondSrc){
      Edge<Location> *e = dst->getInfo().getPathD();
      path.push(dst->getInfo().getId());
      dst = e->getOrig();
    }
    path.push(secondSrc->getInfo().getId());

    output_path(path);
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
    Vertex<Location> *v1 = graph.findVertex(Location("",a.first,"nullptr",false));
    Vertex<Location> *v2 = graph.findVertex(Location("",a.second,"nullptr",false));
    for (Edge<Location> *e: v1->getAdj()) {
      Vertex<Location> *w = e->getDest();
      if (w->getInfo().getId() == a.second) {
        e->setSelected(true);
        break;
      }
    }
    for (Edge<Location> *e: v2->getAdj()) {
      Vertex<Location> *w = e->getDest();
      if (w->getInfo().getId() == a.first) {
        e->setSelected(true);
        break;
      }
    }
  }

  distra(graph,src,nullptr,0);       //driving
  distra(graph,dst,nullptr,1);   //walking

  bool flag_max = true;
  bool flag_no_path = true;

  Vertex<Location> *best = nullptr;
  double bestDistance = INF;
  for (Vertex<Location> *v: graph.getVertexSet()) { //complexidade O(|V|)
    if (v->getInfo().getHasParking()) {
      if (v->getInfo().getPathD() == nullptr || v->getInfo().getPathW() == nullptr ) continue;
      flag_no_path = false;
      if (v->getInfo().getDistW() > maxWalkTIme) continue;
      flag_max = false;
      if (bestDistance > v->getInfo().getDistD() + v->getInfo().getDistW()) {
        bestDistance = v->getInfo().getDistD() + v->getInfo().getDistW();
        best = v;
      }
      else if (bestDistance == v->getInfo().getDistD() + v->getInfo().getDistW()) {
        if (best->getInfo().getDistW() < v->getInfo().getDistW()) {
          best = v;
        }
      }
    }
  }

  if (flag_max || flag_no_path) {
    std::cout << "DrivingRoute:none" << std::endl;
    std::cout << "ParkingNode:none" << std::endl;
    std::cout << "WalkingRoute:none" << std::endl;
    std::cout << "TotalTime:" << std::endl;
    if (flag_no_path)
      std::cout << "No path FOUND" << std::endl;
    else{
      std::cout << "Message:No possible route with max. walking time of " << maxWalkTIme <<" minutes." << std::endl;
      algorithm3_2(graph,source,dest,maxWalkTIme);
    }
  }
  else {
    Vertex<Location> * v;
    v = best;
    std::cout << "DrivingRoute:";
    std::stack<int> path;
    while (v != src){
      Edge<Location> *e = v->getInfo().getPathD();
      path.push(v->getInfo().getId());
      v = e->getOrig();
    }
    path.push(src->getInfo().getId());

    while (path.size() > 1) {
      std::cout << path.top() << ",";
      path.pop();
    }
    std::cout << path.top()
    << "(" << best->getInfo().getDistD() << ")" << std::endl;
    path.pop();

    std::cout << "ParkingNode:";
    std::cout << best->getInfo().getId() << std::endl;

    std::cout << "WalkingRoute:";

    v = best;

    while (v != dst){
      Edge<Location> *e = v->getInfo().getPathW();
      std::cout << v->getInfo().getId() << ",";
      v = e->getOrig();
    }
    std::cout << v->getInfo().getId()<< "(" << best->getInfo().getDistW() << ")" << std::endl;
    std::cout << "TotalTime:" << bestDistance << std::endl;
  }

}

void Algorithm::algorithm3_2(Graph<Location> & graph, const int& source, const int& dest,const int & maxWalkTIme){
    Vertex<Location> *src = graph.findVertex(Location("",source,"nullptr",false));
    Vertex<Location> *dst = graph.findVertex(Location("",dest,"nullptr",false));

    Vertex<Location> *best_alternative = nullptr;
    Vertex<Location> *second_best_alternative = nullptr;
    double bestDistance = INF;
    double secondBestDistance = INF;

    for (Vertex<Location> *v: graph.getVertexSet()) { //complexidade O(|V|)
        if (v->getInfo().getHasParking()) {
            if (v->getInfo().getPathD() == nullptr || v->getInfo().getPathW() == nullptr ) continue;
            if (bestDistance > v->getInfo().getDistD() + v->getInfo().getDistW()) {
                second_best_alternative = best_alternative;
                secondBestDistance = bestDistance;
                bestDistance = v->getInfo().getDistD() + v->getInfo().getDistW();
                best_alternative = v;
            }
            else if (bestDistance == v->getInfo().getDistD() + v->getInfo().getDistW()) {
                if (best_alternative->getInfo().getDistW() < v->getInfo().getDistW()) {
                    second_best_alternative = best_alternative;
                    secondBestDistance = bestDistance;
                    best_alternative = v;
                }
            }
            else if (secondBestDistance > v->getInfo().getDistD() + v->getInfo().getDistW()) {
              secondBestDistance = v->getInfo().getDistD() + v->getInfo().getDistW();
              second_best_alternative = v;
            }
            else if (secondBestDistance == v->getInfo().getDistD() + v->getInfo().getDistW()) {
              if (second_best_alternative->getInfo().getDistW() < v->getInfo().getDistW()) {
                second_best_alternative = v;
              }
            }
        }
    }

    std::cout << std::endl <<"Best alternatives:"<< std::endl;
    std::cout << "Source:" << source << std::endl;
    std::cout << "Destination:" << dest << std::endl;
    Vertex<Location> * v;
    v = best_alternative;
    std::cout << "DrivingRoute:";
    std::stack<int> path;
    while (v != src){
        Edge<Location> *e = v->getInfo().getPathD();
        path.push(v->getInfo().getId());
        v = e->getOrig();
    }
    path.push(src->getInfo().getId());

    while (path.size() > 1) {
        std::cout << path.top() << ",";
        path.pop();
    }
    std::cout << path.top()
    << "(" << best_alternative->getInfo().getDistD() << ")" << std::endl;
    path.pop();

    std::cout << "ParkingNode:";
    std::cout << best_alternative->getInfo().getId() << std::endl;

    std::cout << "WalkingRoute:";

    v = best_alternative;

    while (v != dst){
        Edge<Location> *e = v->getInfo().getPathW();
        std::cout << v->getInfo().getId() << ",";
        v = e->getOrig();
    }
    std::cout << v->getInfo().getId()<< "(" << best_alternative->getInfo().getDistW() << ")" << std::endl;
    std::cout << "TotalTime:" << bestDistance << std::endl;

    std::cout << "DrivingRoute:";
    v = second_best_alternative;
    while (v != src){
        Edge<Location> *e = v->getInfo().getPathD();
        path.push(v->getInfo().getId());
        v = e->getOrig();
    }
    path.push(src->getInfo().getId());

    while (path.size() > 1) {
        std::cout << path.top() << ",";
        path.pop();
    }
    std::cout << path.top()
    << "(" << second_best_alternative->getInfo().getDistD() << ")" << std::endl;
    path.pop();

    std::cout << "ParkingNode:";
    std::cout << second_best_alternative->getInfo().getId() << std::endl;

    std::cout << "WalkingRoute:";

    v = second_best_alternative;

    while (v != dst){
        Edge<Location> *e = v->getInfo().getPathW();
        std::cout << v->getInfo().getId() << ",";
        v = e->getOrig();
    }
    std::cout << v->getInfo().getId()<< "(" << second_best_alternative->getInfo().getDistW() << ")" << std::endl;
    std::cout << "TotalTime:" << secondBestDistance << std::endl;
}

#endif //ALGORITHM_H
