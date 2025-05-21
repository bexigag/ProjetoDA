//
// Created by gonca on 12/05/2025.
//

#ifndef ILP_H
#define ILP_H

#include <iostream>
#include <vector>
#include "../data_structures/Graph.h"
#include "../parse/Pallet.h"
#include "Outinho.h"
#include "Utils.h"
#include <limits>
#include <chrono>
#include <stack>
#include "Outinho.h"

using namespace std;

namespace ILP {
    void run(int capacity, int n_pallets, Pallet * pallets){

      	auto start = std::chrono::high_resolution_clock::now();

        cout << "Optimal solution using ILP approach: "<< endl;

        if (capacity < 0 or n_pallets < 0 or pallets==nullptr){
            cout << "no possible result" << endl;
            return;
        }

        bool usedItems[n_pallets];

        auto end = std::chrono::high_resolution_clock::now();


        Outinho::terminal_output(n_pallets,pallets,usedItems,start, end);
    }


    void runLP(int capacity, int n_pallets, Pallet * tempPallets){


    }
}

#endif //ILP_H
