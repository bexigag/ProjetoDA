//
// Created by gonca on 09/03/2025.
//

#ifndef PARSE_H
#define PARSE_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Pallet.h"

using namespace std;

namespace Parse{

    int readTruckAndPallets(int &capacity, int &n_pallets) {
        cout << "Capacity,Pallets" << endl;
        string input;
        getline(cin, input);  // lê a linha toda
        getline(cin, input);  // lê a linha toda

        stringstream ss(input);
        char separador;

        // tenta extrair os dois inteiros separados por uma vírgula
        if ((ss >> capacity >> separador >> n_pallets) && separador == ',') {
            return 0; // sucesso
        } else {
            return 1; // erro na leitura/formatação
        }
    }

    int readPallets(Pallet *& pallets,int n_pallets) {
        cout << "Pallet,Weight,Profit" << endl;
        if (pallets != nullptr) {
            delete[] pallets;
            pallets = nullptr;
        }

        pallets = new Pallet[n_pallets];

        string input;
        char separador1;
        char separador2;

        int index = 0;

        while (index < n_pallets && getline(cin, input)) {
            stringstream ss(input);
            int id;
            int weight;
            int profit;
            // tenta extrair os dois inteiros separados por uma vírgula
            if ((ss >> id >> separador1 >> weight >> separador2 >> profit) && separador1 == ',' && separador2 == ',') {
                pallets[index]= {id, weight, profit}; // sucesso
                //cout << pallets[index].id << endl;
                index++;
            } else {
                return 1; // erro na leitura/formatação
            }
        }
        return 0;
    }

    void displayInput(int & capacity,int & n_pallets, Pallet * pallets) {
        cout <<  "O truck tem capacidade: " << capacity << endl;
        cout << "Tem "<< n_pallets << " pallets:" << endl;
        cout << "id   weight   profit" << endl;
        for (int i = 0; i < n_pallets; i++) {
            cout << pallets[i].id << " " << pallets[i].weight << " " << pallets[i].profit  << endl;
        }
    }

    void clearInput(int & capacity,int & n_pallets, Pallet * pallets) {
        capacity = -1;
        n_pallets = -1;
        delete[] pallets;
        pallets = nullptr;
    }

};


#endif //PARSE_H
