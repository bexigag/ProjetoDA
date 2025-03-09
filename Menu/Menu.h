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
    static void run();

private:
    string mode;
    int source;
    int dest;
    vector<int> avoidNodes;
    vector<pair<int,int>> avoidSegments;
    int includeNode;
    Graph<Location> graph;
};


void Menu::run() {
    cout << "Menu" << endl;
    cout << "1 Parse Input Data" << endl;
    cout << "2 Route Planning Functionalities (driving only)" << endl;
    cout << "3 Environmentally-Friendly Route Planning (driving and walking)" << endl;
    cout << "4 Exit" << endl;

    bool flag = true;
    while(flag) {
        int option;
        cin >> option;
        switch(option) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                flag = false;
            break;
            default:
                cout << "Seu burro, só podes escolher até 4" << endl;
        }

    }
}



#endif //MENU_H