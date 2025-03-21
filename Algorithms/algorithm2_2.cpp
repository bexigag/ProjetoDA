#include "Algorithm.h"

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