#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include "../parse/parse.h"
#include "../data_structures/Graph.h"
#include "../Algorithms/Algorithm.h"
#include "../parse/Pallet.h"
#include "../Algorithms/Brute_force.h"
#include "../Algorithms/Dynamic.h"
#include "../Algorithms/Greedy.h"
#include "../Algorithms/Outinho.h"


using namespace std;

class Menu{
public:

    Menu() {}

    void run();

private:

    int n_pallets = -1;

    int capacity = -1;

    Pallet * pallets = nullptr;

    Algorithm algorithm;
};


void Menu::run() {

    bool flag = true;
    while(flag) {
        int option;
        cout << "Menu" << endl;
        cout << "1 Read Input" << endl;
        cout << "2 Display Input" << endl;
        cout << "4 Run" << endl;
        cout << "5 Clear Input" << endl;
        cout << "7 Exit" << endl;
        cout << "Choose an option:" << endl;
        cin >> option;
        if (option == 1) {
            if (Parse::readTruckAndPallets(capacity, n_pallets)) {
                cout << "Mau input, reset input..." << endl;
                Parse::clearInput(capacity, n_pallets, pallets);
                break;
            }
            if (Parse::readPallets(pallets, n_pallets)) {
                cout << "Mau input, reset input..." << endl;
                Parse::clearInput(capacity, n_pallets, pallets);
            }
        }
        else if (option == 2) {
            Parse::displayInput(capacity, n_pallets, pallets);
        }
        else if (option == 3) {
        }
        else if (option == 4) {
            int option;
            cout << "1 Run Brute Force aproach" << endl;
            cout << "2 Run Dynamic programming aproach" << endl;
            cout << "3 Run Greedy aproach" << endl;
            cout << "4 Run Integer Linear programming aproach" << endl;
            cout << "Choose an option:" << endl;
            cin >> option;
            if (option == 1) {
                int optionbruteforce;
                cout << "1 Run Brute Force" << endl;
                cout << "2 Run Brute Force with Backtracking" << endl;

                cin >> optionbruteforce;

                if (optionbruteforce == 1) {
                    Brute_force::run(capacity, n_pallets, pallets);
                }
                else if (optionbruteforce == 2) {
                    Brute_force::run_backtracking(capacity, n_pallets, pallets);
                }
            }
            else if (option == 2) {
                Dynamic::run(capacity, n_pallets, pallets);
            }
            else if (option == 3) {
                int optionGreedy;
                cout << "1 Run Greedy by Density" << endl;
                cout << "2 Run Greedy by Value" << endl;

                cin >> optionGreedy;
                if (optionGreedy == 1) {
                    Greedy::runDensity(capacity, n_pallets, pallets);
                }
                else if (optionGreedy == 2) {
                    Greedy::runValue(capacity, n_pallets, pallets);
                }
                else if (optionGreedy == 3) {
                    Greedy::run2Aproximation(capacity, n_pallets, pallets);
                }
            }
            else if (option == 4) {

            }
            else {
                cout << "invalid input" << endl;
            }
        }
        else if (option == 5) {
            Parse::clearInput(capacity, n_pallets, pallets);
        }
        else if (option == 6) {

        }
        else if (option == 7) {
            Parse::clearInput(capacity, n_pallets, pallets);
            flag = false;
        }
        else {
            cout << "invalid input" << endl;
        }
    }
}


#endif //MENU_H