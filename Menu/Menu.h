#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include "../parse/parse.h"
#include "../data_structures/Graph.h"
#include "../Algorithms/Algorithm.h"

using namespace std;


class Menu{
public:
    /**
* @brief empty constructor of the Menu class
* @return Menu
*/
    Menu() {
        graph = new Graph<Location>();
    }


    /**
* @brief function that allows the program to run
* @return void
*/
    void run();

private:
    string mode = " ";
    int source = -1;
    int dest = -1;
    vector<int> avoidNodes; //can be empty
    vector<pair<int,int>> avoidSegments; //can be empty
    int includeNode = -1; //can be  empty
    int maxWalkTime = -1;

    Graph<Location> * graph;

    Parse parse;
    Algorithm algorithm;
};


void Menu::run() {

    bool flag = true;
    while(flag) {
        int option;
        cout << "Menu" << endl;
        cout << "0 Read graph" << endl;
        cout << "1 Read input" << endl;
        cout << "2 Display input" << endl;
        cout << "3 Display graph" << endl;
        cout << "4 Run" << endl;
        cout << "5 Clear Input" << endl;
        cout << "6 Clear Graph" << endl;
        cout << "7 Exit" << endl;
        cout << "Choose an option:" << endl;
        cin >> option;
        if (option == 0) {
            parse.readLocations(graph);
            parse.readDistances(graph);
        }
        else if (option == 1) {
            parse.readInput(mode, source,dest,maxWalkTime,includeNode,avoidNodes,avoidSegments);
        }
        else if (option == 2) {
            parse.displayInput(mode, source,dest,maxWalkTime,includeNode,avoidNodes,avoidSegments);
        }
        else if (option == 3) {
            parse.displayGraph(graph);
        }
        else if (option == 4) {
            algorithm.runAlgorithm(graph,mode,source,dest,maxWalkTime,includeNode,avoidNodes,avoidSegments);
        }
        else if (option == 5) {
            source = -1;
            dest = -1;
            maxWalkTime = -1;
            includeNode = -1;
            avoidNodes.clear();
            avoidSegments.clear();
        }
        else if (option == 6) {
            if (graph != nullptr) {
                delete graph;
            }
            graph = new Graph<Location>();
        }
        else if (option == 7) {
            flag = false;
        }
        else {
            cout << "invalid input" << endl;
        }
    }
}


#endif //MENU_H