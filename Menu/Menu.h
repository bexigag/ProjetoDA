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
        else if (option == 2) {
        }
        else if (option == 3) {
        }
        else if (option == 4) {
            Brute_force brute_force;
            brute_force.run(capacity, n_pallets, pallets);

            Dynamic dynamic;
            dynamic.run(capacity, n_pallets, pallets);
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