//
// Created by gonca on 27/03/2025.
//

#ifndef UTILS_H
#define UTILS_H

#include "Algorithm.h"

class Utils{
  public:
    Utils();

    /**
      * @brief outputs the ids of the nodes that are included in the path
      * Time complexity: O(E)
      *
      * @param path stack with the ids of the nodes included in the path
      * @return void
      */
    void output_path(std::stack<int> & path);

    /**
      * @brief resets the isProcessing attribute of the
      * vertexes of the graph and the isSelected attribute
      * of the edges
      * Time complexity: O(V+E)
      *
      * @param graph the input graph of type Location
      * @return void
      */
    void resetGraph(Graph<Location> * graph);

    /**
      * @brief resets both the driving and
      * walking paths (pathW and pathD)
      * Time complexity: O(V)
      *
      * @param graph the input graph of type Location
      * @return void
      */
    void resetPaths(Graph<Location> * graph);


    void restrict(Graph<Location> * graph, const std::vector<int>& avoidNodes, const std::vector<std::pair<int,int>> &avoidSegments);


};

#endif //UTILS_H
