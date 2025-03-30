//
// Created by gonca on 27/03/2025.
//

#ifndef OUTINHO_H
#define OUTINHO_H

#include "../data_structures/Graph.h"
#include "../parse/Location.h"

class Outinho{
  public:
    Outinho();
    void static out_2_1( Vertex<Location> *src, Vertex<Location> *dst);
    void static out_2_2( Vertex<Location> *src, Vertex<Location> *dst, bool comma);
    void static out_3(Vertex<Location> *src,Vertex<Location> *dst, Vertex<Location> * best,double bestDistance);
  private:
    void static output_path(std::stack<int> & path);
};

void Outinho::output_path(std::stack<int> & path) {
    while (!path.empty()) {
        std::cout << path.top();
        path.pop();
        if (!path.empty()){std::cout << ",";}
    }
}

void Outinho::out_2_1( Vertex<Location> *src, Vertex<Location> *dst){
    std::stack<int> path;
    Vertex<Location> *v = dst;

    if (v->getInfo().getPathD() == nullptr) {
        std::cout << "none" << std::endl;
    }
    else {
        path.push(v->getInfo().getId());
        v = v->getInfo().getPathD()->getOrig();
        while (v != src){ //O(V)
            Edge<Location> *e = v->getInfo().getPathD();
            path.push(v->getInfo().getId());
            v->setProcessing(true);
            v = e->getOrig();
        }
        path.push(src->getInfo().getId());
        output_path(path);
        std::cout<< "(" << dst->getInfo().getDistD() << ")"<< std::endl;
    }
}

void Outinho::out_2_2(Vertex<Location> *src,Vertex<Location> *dst, bool comma){
    std::stack<int> path;
    Vertex<Location> *v = dst;

    if (dst->getInfo().getPathD() == nullptr) {
        std::cout << "none" << std::endl;
    }
    else {
        if (comma) {
            v = v->getInfo().getPathD()->getOrig();
        }
        while (v != src) {
            Edge<Location> *e = v->getInfo().getPathD();
            path.push(v->getInfo().getId());
            v = e->getOrig();
        }
        path.push(src->getInfo().getId());

        while (!path.empty()) {
            std::cout << path.top();
            path.pop();
            if (comma || !path.empty()) {
                std::cout << ",";
            }
        }
    }
}

void Outinho::out_3( Vertex<Location> *src,Vertex<Location> *dst, Vertex<Location> * best,double bestDistance ){
    if (best==nullptr) {
        std::cout << std::endl <<"No more possible alternatives"<< std::endl;
        std::cout << std::endl;
        return;
    }
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

#endif //OUTINHO_H
