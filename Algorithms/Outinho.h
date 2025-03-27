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
    void static out_3_1(Vertex<Location> *src, Vertex<Location> *dst);
    void static out_3_2( Vertex<Location> *src, Vertex<Location> *dst);
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
        v = v->getInfo().getPathD()->getOrig();
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

void Outinho::out_3_1( Vertex<Location> *src,Vertex<Location> *dst){

}
void Outinho::out_3_2( Vertex<Location> *src,Vertex<Location> *dst){

}
#endif //OUTINHO_H
