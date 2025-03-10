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
    int includeNode = -1; //can be  empty
    int maxWalkTime = -1;
    Graph<Location> graph;
    Parse parse;
};


void Menu::run() {

    bool flag = true;
    while(flag) {
        int option;
        cout << "Menu (input a number >9 to run)" << endl;
        cout << "0 Read graph" << endl;
        cout << "1 Display input" << endl;
        cout << "2 Read input" << endl;
        cout << "3 Display graph" << endl;
        cout << "4 Choose AvoidNodes" << endl;
        cout << "5 Choose AvoidSegments" << endl;
        cout << "6 Choose IncludeNode" << endl;
        cout << "7 Choose MaxWalkTime" << endl;
        cout << "8 Reset" << endl;
        cout << "9 Exit" << endl;
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