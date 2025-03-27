//
// Created by Lenovo on 27/03/2025.
//

#ifndef UTILS_H
#define UTILS_H

#include "Algorithm.h"

class Utils{
  public:
    Utils();

    /**
   * @brief performs a djikstra in the graph
   *like it was demonstrated in the previous
   *lessons that updates the nodes distances
   *with the minimum distance to a source vertex
   *and a destination vertex
   *Time complexity:O((V+E) log V)
   *
   * @param graph the input graph of type Location
   * @param src source vertex of type Location from
   * which the djikstra will start
   * @param dst destination vertex of type Location
   * from which the djikstra will end
   * @param d_w integer that works as an indicator of the mode of the path
   * (if d_w==0 the mode is driving else if d_w==1 the mode is walking)
   * @return void
   */
    static void distra(Graph<Location> * graph, Vertex<Location> *src,Vertex<Location> *dst , const int d_w);


    /**
      * @brief resets the isProcessing attribute of the
      * vertexes of the graph and the isSelected attribute
      * of the edges
      * Time complexity: O(V+E)
      *
      * @param graph the input graph of type Location
      * @return void
      */
    static void resetGraph(Graph<Location> * graph);

    /**
      * @brief resets both the driving and
      * walking paths (pathW and pathD)
      * Time complexity: O(V)
      *
      * @param graph the input graph of type Location
      * @return void
      */
    static void resetPaths(Graph<Location> * graph);


  /**
    * @brief restricts the path to respect
    * the avoidNodes and avoidSegments parameters
    *
    * @param graph the input graph of type Location
    * @param avoidNodes vector<int> that has the Ids of
    * the nodes that must be avoided in the path
    * @param avoidSegments vector<pair<int,int>> of the
    * edges that must be avoided in the path
    * @return void
    */
  static void restrict(Graph<Location> * graph, const std::vector<int>& avoidNodes, const std::vector<std::pair<int,int>> &avoidSegments);


};


void Utils::resetPaths(Graph<Location> * graph) {
  for (Vertex<Location> *v :graph->getVertexSet()) {
    v->getInfo().setPath(nullptr,2);
  }
}

void Utils::resetGraph(Graph<Location> * graph) {
  for (Vertex<Location> *v :graph->getVertexSet()) {
    v->setProcessing(false);
    v->getInfo().setPath(nullptr,2);
    for (Edge<Location> *e : v->getAdj()) {
      e->setSelected(false);
    }
  }
}





void Utils::distra(Graph<Location> * graph, Vertex<Location> *src,Vertex<Location> *dst ,const int d_w){
  MutablePriorityQueue<Vertex<Location>> pq;

  //O(V)
  for (Vertex<Location> *v :graph->getVertexSet()){
    v->setVisited(false);
    v->setDist(INF);
  }

  src->setDist(0);

  //O(V)
  for (Vertex<Location> *v :graph->getVertexSet()){
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
    //O(E)
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


void Utils::restrict(Graph<Location> * graph, const std::vector<int>& avoidNodes, const std::vector<std::pair<int,int>> &avoidSegments){
  for (int id: avoidNodes) {
    graph->findVertexById(id)->setProcessing(true);
  }

  for (std::pair a: avoidSegments) {
    Vertex<Location> *v1 = graph->findVertexById(a.first);
    Vertex<Location> *v2 = graph->findVertexById(a.second);
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

}

#endif //UTILS_H