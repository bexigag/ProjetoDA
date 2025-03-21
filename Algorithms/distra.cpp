#include "Algorithm.h"

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