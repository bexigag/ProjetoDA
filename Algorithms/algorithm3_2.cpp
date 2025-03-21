#include "Algorithm.h"

void algorithm3_2(Graph<Location> & graph, const int& source, const int& dest,const int & maxWalkTIme){
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
                bestDistance = v->getInfo().getDistD() + v->getInfo().getDistW();
                second_best_alternative = best_alternative;
                secondBestDistance = bestDistance;
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
    std::cout << "TotalTime:" << bestDistance << std::endl;
}