//
// Created by Lenovo on 21/04/2025.
//

#ifndef DYNAMIC_H
#define DYNAMIC_H

#include <iostream>
#include <vector>
#include "../parse/Pallet.h"
#include "Outinho.h"
#include <chrono>
#include <limits>
#include <stack>
#include "Outinho.h"


using namespace std;

namespace Dynamic {
    void runDynamic(int capacity, int n_pallets, Pallet * pallets){
        auto start = std::chrono::high_resolution_clock::now();


        cout << "Optimal solution using dynamic programming approach: "<< endl;

        if (capacity==-1 or n_pallets==-1 or pallets==nullptr){
            cout << "no possible result" << endl;
            return;
        }

       // unsigned int val[n_pallets + 1][capacity+1];
       vector<vector<unsigned int>> val(n_pallets + 1, vector<unsigned int>(capacity + 1, 0));


        for (unsigned int i = 0; i <= n_pallets; i++) {
            for (unsigned int j = 0; j <= capacity; j++) {
                if (i==0 || j==0) {
                    val[i][j] = 0;
                }
                else if (j>=pallets[i-1].weight) {
                    val[i][j] = max(val[i-1][j], val[i-1][j-pallets[i-1].weight]+pallets[i-1].profit);
                }
                else {
                    val[i][j] = val[i-1][j];
                }
            }
        }

        bool usedItems[n_pallets] {false};

        unsigned int max = val[n_pallets][capacity];
        unsigned int index=n_pallets;
        unsigned int j=capacity;

        while (index>0) {
            auto current = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::seconds>(current - start);
            if (duration>=std::chrono::seconds(10)) {
                cout << "Too much time! It took more than 10 seconds! Choose another algorithm!" << endl;
                return;
            }
            if (j>=pallets[index-1].weight and max>val[index-1][j]) {
                max = val[index-1][j-pallets[index-1].weight];
                usedItems[index-1] = true;
                j-=pallets[index-1].weight;
            }
            index--;
        }

        auto end = std::chrono::high_resolution_clock::now();

        Outinho::terminal_output(n_pallets,pallets,usedItems,start, end);
    }

}

#endif //DYNAMIC_H
