#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include "../parse/parse.h"
#include "../data_structures/Graph.h"
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
    int includeNode = -1; //can be empty
    int maxWalkTime = -1;
    Graph<Location> graph;
};


void Menu::run() {

    bool flag = true;
    while(flag) {
        int option;
        cout << "Menu (input a number >9 to run)" << endl;
        cout << "0 Parse Input Data" << endl;
        cout << "1 Choose Mode" << endl;
        cout << "2 Choose source" << endl;
        cout << "3 Choose Destination" << endl;
        cout << "4 Choose AvoidNodes" << endl;
        cout << "5 Choose AvoidSegments" << endl;
        cout << "6 Choose IncludeNode" << endl;
        cout << "7 Choose MaxWalkTime" << endl;
        cout << "8 Reset" << endl;
        cout << "9 Exit" << endl;
        cout << "Choose an option:" << endl;
        cin >> option;
        if (option == 0) {
            string filename;
            cout << "Enter file name or 'Graph' to build graph using Distances.csv and Locations.csv: " << endl;
            cin >> filename;
            Parse parse;
            if (filename == "Graph") {
                parse.readLocations(graph);
                parse.readDistances(graph);
            }
            else {
                parse.readInput(filename, source, dest, maxWalkTime, includeNode, avoidNodes, avoidSegments);
            }
        }
        else if (option == 1) {
            cout << "Enter mode: " << endl;
            cout << "1 driving " << endl;
            cout << "2 driving-walking " << endl;
            int m;
            cin >> m;
            if (m == 1) mode = "driving";
            else if (m == 2) mode = "driving-walking";
        }
        else if (option == 2) {
            cout << "Enter source: " << endl;
            cin >> source;
        }
        else if (option == 3) {
            cout << "Enter destination: " << endl;
            cin >> dest;
        }
        else if (option == 4) {
            avoidNodes.clear();
            cout << "Enter avoidNodes (one at a time, to stop insert -1): " << endl;
            int a;
            cin >> a;
            while (a != -1) {
                avoidNodes.push_back(a);
                cin >> a;
            }
        }
        else if (option == 5) {
            avoidNodes.clear();
            cout << "Enter avoidSegments (one at a time, and in pairs, to stop insert -1): " << endl;
            int b;
            int c;
            cin >> b;
            cin >> c;
            while (b != -1 && c != -1) {
                avoidSegments.push_back({b, c});
                cout << "Added (" << b << "," << c << ")" << endl;
                cin >> b;
                cin >> c;
            }
        }
        else if (option == 6) {
            cout << "Enter IncludeNode: " << endl;
            cin >> includeNode;
        }
        else if (option == 7) {
            cout << "Enter MaxWalkTime: " << endl;
            cin >> maxWalkTime;
        }
        else if (option == 8) {
            source = -1;
            dest = -1;
            maxWalkTime = -1;
            includeNode = -1;
            avoidNodes.clear();
            avoidSegments.clear();
        }
        else if (option == 9) {
            flag = false;
        }
        else {
            cout << "Seu burro, só podes escolher até 4" << endl;
        }
    }
}



#endif //MENU_H