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
    Menu(){}
    string getfilename();
    void run();

private:
    string mode = " ";
    int source = -1;
    int dest = -1;
    vector<int> avoidNodes; //can be empty
    vector<pair<int,int>> avoidSegments; //can be empty
    int includeNode = -1; //can be  empty
    int maxWalkTime = -1;
    Graph<Location> graph;
    Parse parse;
    Algorithm algorithm;
};


void Menu::run() {

    bool flag = true;
    while(flag) {
        int option;
        cout << "Menu" << endl;
        cout << "0 Read graph" << endl;
        cout << "1 Display input" << endl;
        cout << "2 Read input" << endl;
        cout << "3 Display graph" << endl;
        cout << "4 Run" << endl;
        cout << "5 Reset" << endl;
        cout << "6 Exit" << endl;
        cout << "Choose an option:" << endl;
        cin >> option;
        if (option == 0) {
            parse.readLocations(graph);
            parse.readDistances(graph);
        }
        else if (option == 1) {
            parse.display(mode, source,dest,maxWalkTime,includeNode,avoidNodes,avoidSegments);
        }
        else if (option == 2) {
            parse.readInput(mode, source,dest,maxWalkTime,includeNode,avoidNodes,avoidSegments);
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
            flag = false;
        }
        else {
            cout << "Seu burro, só podes escolher até 4" << endl;
        }
    }
}


#endif //MENU_H