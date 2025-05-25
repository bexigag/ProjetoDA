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


    /**
    * @brief Reads the input of the max capacity
    * and the number of pallets
    * sequence: Capacity,Pallets
    * @param capacity max weight
    * @param n_pallets number of pallets
    * to be stored
    * @return void
    */
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

    /**
    * @brief Reads the input of each pallet
    * and associated weight and profit
    * sequence: Pallet,Weight,Profit
    * @param pallets pointer to the object Pallet
    * @param n_pallets number of pallets
    * to be stored
    * @return void
    */
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



    /**
    * @brief Reads the input of each pallet
    * and associated weight and profit
    * sequence: Pallet,Weight,Profit
    * @param capacity pointer to the object Pallet
    * @param pallets pointer to the object Pallet
    * @param n_pallets number of pallets
    * to be stored
    * @return void
    */
    void displayInput(int & capacity,int & n_pallets, Pallet * pallets) {
        cout <<  "O truck tem capacidade: " << capacity << endl;
        cout << "Tem "<< n_pallets << " pallets:" << endl;
        cout << "id   weight   profit" << endl;
        for (int i = 0; i < n_pallets; i++) {
            cout << pallets[i].id << " " << pallets[i].weight << " " << pallets[i].profit  << endl;
        }
    }


    /**
    * @brief clears the input
    * @param capacity pointer to the object Pallet
    * @param pallets pointer to the object Pallet
    * @param n_pallets number of pallets
    * @return void
    */
    void clearInput(int & capacity,int & n_pallets, Pallet *& pallets) {
        capacity = -1;
        n_pallets = -1;
        delete[] pallets;
        pallets = nullptr;
    }

}


#endif //PARSE_H
