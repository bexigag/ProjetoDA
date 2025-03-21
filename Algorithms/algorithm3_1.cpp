#include "Algorithm.h"

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