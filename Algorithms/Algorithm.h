//
// Created by gonca on 13/03/2025.
//

#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <iostream>
#include <vector>
#include "../data_structures/Graph.h"
#include "../parse/Location.h"
#include "Outinho.h"
#include "Utils.h"
#include <limits>
#include <stack>

/**
 * @class Algorithm
 * @brief This class is responsible for implementing the
 * algorithms of the project
 *
 */
class Algorithm{
    public:
     /**
     * @brief Empty constructor of the Algorithm class
     */
      Algorithm(){}
    /**
     * @brief chooses the right algorithm accordingly to the input provided

     *
     * @param graph the input graph of type Location
     * @param mode string that indicates the mode of the path (driving or driving-walking)
     * @param source integer that indicates the id of the source node
     * @param dest integer that indicates the id of the destination node
     * @param maxWalkTime integer that indicates the maxWalktime
     * @param includeNode integer that indicates the id of the node that must be included in the path
     * @param avoidNodes vector of the ids (integers) of the nodes that cannot be included in the path
     * @param avoidSegments vector of the edges that cannot be included in the path
     * @return void
     */
      void runAlgorithm(Graph<Location> * graph, const std::string& mode,const int & source,const int & dest,const int & maxWalkTime,const int & includeNode,const std::vector<int> &avoidNodes,const std::vector<std::pair<int,int>> &avoidSegments);
    private:
  /**
      * @brief  Independent Route Planning: this algorithm determines the shortest path
      * between a source node and a destination node. Besides that,
      * it also identifies an alternative route knowing that
      * the two routes share no intermediate nodes or segments, except
      * for the source and destination, and also the alternative route
      * is equal to or greater in travel time compared to the primary route.
      * Time complexity: O((V+E)logV)
      *
      * @param graph the input graph of type Location
      * @param source integer that indicates the id of the source node
      * @param dest integer that indicates the id of the destination node
      * @return void
      */
     void algorithm2_1(Graph<Location> * graph, Vertex<Location> *src, Vertex<Location> *dst); //not restricted

  /**
    * @brief Restricted Route Planning:  this algorithm determines the shortest path
    * possible between a source node and a destination node. However, this path as some
    * restrictions that it must comply (includeNode,avoidNodes and avoidSegments)
    * Time complexity: O((V+E) log V) dominated by djikstra
    *
    * @param graph the input graph of type Location
    * @param source integer that indicates the id of the source node
    * @param dest integer that indicates the id of the destination node
    * @param includeNode integer that indicates the id of the node that must be included in the path
    * @param avoidNodes vector of the Ids (integers) of the nodes that cannot be included in the path
    * @param avoidSegments vector of the edges that cannot be included in the path
    * @return void
    */
     void algorithm2_2(Graph<Location> * graph, Vertex<Location> *src,Vertex<Location> *dst, const int& includeNode, const std::vector<int>& avoidNodes, const std::vector<std::pair<int,int>> &avoidSegments);

  /**
    * @brief  Best route for driving and walking: shortest path
    * between a source node and a destination node in which firstly
    * the path should be done by driving and then stopping at some node
    * with parking and afterward the path should be done by walking
    * complying the restrictions that are inserted (avoidNodes,
    * avoidSegments and maxWalkTime)
    * Time complexity: O((V+E) log V) dominated by djikstra
    *
    * @param graph the input graph of type Location
    * @param source integer that indicates the id of the source node
    * @param dest integer that indicates the id of the destination node
    * @param avoidNodes vector of the ids (integers) of the nodes that cannot be included in the path
    * @param avoidSegments vector of the edges that cannot be included in the path
    * @param maxWalkTIme integer indicating the max walk time of the path
    * @return void
    */
     void algorithm3_1(Graph<Location> * graph, Vertex<Location> *src,Vertex<Location> *dst,const std::vector<int>& avoidNodes, const std::vector<std::pair<int,int>> &avoidSegments,const int & maxWalkTIme);

  /**
  * @brief Approximate Solution: If no suitable route is found, display a list of suggestions
      * representing the best feasible alternative routes that approximate user requirements
      * Besides that, present 2 alternatives, sorted by overall travel time, but always including
      * a driving and a walking segment
      * Time complexity: O(V)
      *
      * @param graph the input graph of type Location
      * @param source integer that indicates the id of the source node
      * @param dest integer that indicates the id of the destination node
      * @param maxWalkTIme integer indicating the max walk time of the path
      * @return void
      */
  void algorithm3_2_No_Walk(Graph<Location> * graph, Vertex<Location> *src,Vertex<Location> *dst);

  /**
  * @brief Approximate Solution: If no suitable route is found, display a list of suggestions
      * representing the best feasible alternative routes that approximate user requirements
      * Besides that, present 2 alternatives, sorted by overall travel time, but always including
      * a driving and a walking segment
      * Time complexity: O((V+E) log V) dominated by djikstra
      *
      * @param graph the input graph of type Location
      * @param source integer that indicates the id of the source node
      * @param dest integer that indicates the id of the destination node
      * @param maxWalkTIme integer indicating the max walk time of the path
      * @return void
      */
  void algorithm3_2_No_Path(Graph<Location> * graph, Vertex<Location> *src,Vertex<Location> *dst, const int & maxWalkTIme);

};

void Algorithm::runAlgorithm(Graph<Location> * graph,const std::string& mode,const int & source,const int & dest,const int & maxWalkTime,const int & includeNode,const std::vector<int> &avoidNodes,const std::vector<std::pair<int,int>> &avoidSegments){
  if (graph->findVertexById(source) == nullptr || graph->findVertexById(dest) == nullptr) {
    std::cout << "Not valid!" << std::endl;
    return;
  }
  Vertex<Location> *src = graph->findVertexById(source);
  Vertex<Location> *dst = graph->findVertexById(dest);
  std::cout << "Source:" << source<<std::endl;
  std::cout << "Destination:"<< dest <<std::endl;
  if (mode == "driving") {
      if (!avoidNodes.empty() || !avoidSegments.empty() ||includeNode != -1) {
        algorithm2_2(graph,src,dst,includeNode,avoidNodes,avoidSegments);
      }
      else algorithm2_1(graph,src,dst);
  }
  else if (mode == "driving-walking") {
    algorithm3_1(graph,src,dst,avoidNodes,avoidSegments,maxWalkTime);
  }
  Utils::resetGraph(graph);

}


void Algorithm::algorithm2_1(Graph<Location> * graph, Vertex<Location> *src,Vertex<Location> *dst) {
  std::cout << "BestDrivingRoute:";

  Utils::distra(graph,src,dst,0); //O((V+E) log V)
  Outinho::out_2_1(src,dst);

  std::cout << "AlternativeDrivingRoute:";

  Utils::resetPaths(graph);
  Utils::distra(graph,src,dst,0);

  Outinho::out_2_1(src,dst);
}

void Algorithm::algorithm2_2(Graph<Location> * graph, Vertex<Location> *src,Vertex<Location> *dst, const int& includeNode, const std::vector<int>& avoidNodes, const std::vector<std::pair<int,int>> &avoidSegments) {

  Utils::restrict(graph,avoidNodes,avoidSegments);

  std::cout << "RestrictedDrivingRoute:";

  int distance = 0;
  std::stack<int> path;
  Vertex<Location> *secondSrc = src;

  if (includeNode != -1) {
    Vertex<Location> *firstDst = graph->findVertexById(includeNode);
    secondSrc = firstDst;
    Utils::distra(graph,src,firstDst,0);

    distance += firstDst->getInfo().getDistD();

    Outinho::out_2_2(src, firstDst,true);
  }

  Utils::distra(graph,secondSrc,dst,0);
  distance += dst->getInfo().getDistD();

  Outinho::out_2_2(secondSrc,dst,false);
  std::cout<< "(" << distance << ")"<< std::endl;
}

void Algorithm::algorithm3_1(Graph<Location> * graph, Vertex<Location> *src,Vertex<Location> *dst,const std::vector<int>& avoidNodes, const std::vector<std::pair<int,int>> &avoidSegments,const int & maxWalkTIme) {

  Utils::restrict(graph,avoidNodes,avoidSegments);

  //O((V+E) log V) + O((V+E) log V)
  Utils::distra(graph,src,nullptr,0);       //driving
  Utils::distra(graph,dst,nullptr,1);   //walking

  bool flag_max = true;
  bool flag_no_path = true;

  Vertex<Location> *best = nullptr;
  double bestDistance = INF;
  for (Vertex<Location> *v: graph->getVertexSet()) { //complexidade O(|V|)
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
    std::cout << std::endl<< "DrivingRoute:none" << std::endl;
    std::cout << "ParkingNode:none" << std::endl;
    std::cout << "WalkingRoute:none" << std::endl;
    std::cout << "TotalTime:" << std::endl;
    if (flag_no_path) {
      std::cout << "Message:No path FOUND with driving and then walking" << std::endl;
      Utils::resetGraph(graph);
      algorithm3_2_No_Path(graph, src, dst, maxWalkTIme);
    }
    else{
      std::cout << "Message:No possible route with max. walking time of " << maxWalkTIme <<" minutes." << std::endl;
      algorithm3_2_No_Walk(graph,src,dst);
    }
  }
  else {
    Outinho::out_3(src, dst, best, bestDistance);
  }
}

void Algorithm::algorithm3_2_No_Walk(Graph<Location> * graph, Vertex<Location> *src,Vertex<Location> *dst){
    std::cout <<std::endl<<  "    Without MaxWalkTime    " << std::endl;

    Vertex<Location> *best_alternative = nullptr;
    Vertex<Location> *second_best_alternative = nullptr;
    double bestDistance = INF;
    double secondBestDistance = INF;

    for (Vertex<Location> *v: graph->getVertexSet()) { //complexidade O(|V|)
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
    std::cout << "Source:" << src->getInfo().getId() << std::endl;
    std::cout << "Destination:" << dst->getInfo().getId() << std::endl;

    Outinho::out_3(src, dst, best_alternative, bestDistance);
    Outinho::out_3(src, dst, second_best_alternative, secondBestDistance);
}

void Algorithm::algorithm3_2_No_Path(Graph<Location> * graph, Vertex<Location> *src,Vertex<Location> *dst, const int& maxWalkTIme){
    std::cout <<std::endl<<  "     Without restrictions    " << std::endl;

    //O((V+E) log V) + O((V+E) log V)
    Utils::distra(graph,src,nullptr,0);       //driving
    Utils::distra(graph,dst,nullptr,1);   //walking

    Vertex<Location> *best_alternative = nullptr;
    Vertex<Location> *second_best_alternative = nullptr;
    double bestDistance = INF;
    double secondBestDistance = INF;

    bool flag_max = true;
    bool flag_no_path = true;

    for (Vertex<Location> *v: graph->getVertexSet()) { //complexidade O(|V|)
        if (v->getInfo().getHasParking()) {
            if (v->getInfo().getPathD() == nullptr || v->getInfo().getPathW() == nullptr ) continue;
            flag_no_path = false;
            if (v->getInfo().getDistW() > maxWalkTIme) continue;
            flag_max = false;
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

  if (flag_max || flag_no_path) {
    std::cout<< std::endl << "DrivingRoute:none" << std::endl;
    std::cout << "ParkingNode:none" << std::endl;
    std::cout << "WalkingRoute:none" << std::endl;
    std::cout << "TotalTime:" << std::endl;
    if (flag_no_path) {
      std::cout << "Message:No path FOUND with driving and then walking" << std::endl;
    }
    else{
      std::cout << "Message:No possible route with max. walking time of " << maxWalkTIme <<" minutes." << std::endl;
      algorithm3_2_No_Walk(graph,src,dst);
    }
  }
  else {
    std::cout << std::endl <<"Best alternatives:"<< std::endl;
    std::cout << "Source:" << src->getInfo().getId() << std::endl;
    std::cout << "Destination:" << dst->getInfo().getId() << std::endl;

    Outinho::out_3(src, dst, best_alternative, bestDistance);
    Outinho::out_3(src, dst, second_best_alternative, secondBestDistance);
  }
}

#endif //ALGORITHM_H
