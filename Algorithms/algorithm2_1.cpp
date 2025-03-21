//
// Created by bexigag on 21/03/2025.
//

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