//
// Created by Lenovo on 21/04/2025.
//

#ifndef DYNAMIC_H
#define DYNAMIC_H

#include <iostream>
#include <vector>
#include "../data_structures/Graph.h"
#include "../parse/Pallet.h"
#include "Outinho.h"
#include <chrono>
#include "Utils.h"
#include <limits>
#include <stack>
#include "Outinho.h"

using namespace std;

namespace Dynamic {
    void run(int capacity, int n_pallets, Pallet * pallets){
        auto start = std::chrono::high_resolution_clock::now();


        cout << "Optimal solution using dynamic programming approach: "<< endl;

        if (capacity==-1 or n_pallets==-1 or pallets==nullptr){
            cout << "no possible result" << endl;
            return;
        }

        unsigned int val[n_pallets + 1][capacity+1];

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

    void runOptimized(int capacity, int n_pallets, Pallet * pallets){

        cout << "Optimal solution using optimized dynamic programming approach: "<< endl;

        if (capacity==-1 or n_pallets==-1 or pallets==nullptr){
            cout << "no possible result" << endl;
            return;
        }

        unsigned int val[2][capacity+1];
        int pred[n_pallets] {-1};
        bool usedItems[n_pallets] {false};

        int item = -1;
        unsigned int i;

        while (item <= n_pallets) {
            i = (item + 1) % 2;
            for (unsigned int j = 0; j <= capacity; j++) {
                if (item==-1 || j==0) {
                    val[i][j] = 0;
                }
                else if (i == 1) {
                    if (j>=pallets[item].weight) {
                        if (val[i-1][j-pallets[item].weight]+pallets[item].profit > val[i-1][j]) {
                            val[i][j] = val[i-1][j-pallets[item].weight]+pallets[item].profit;
                            if (j-pallets[item].weight > 0) {
                                pred[item] = item - 1;
                            }
                        }
                    }
                    else {
                        val[i][j] = val[i-1][j];
                    }
                }
                else {
                    if (j>=pallets[item].weight) {
                        val[i][j] = max(val[i+1][j], val[i+1][j-pallets[item].weight]+pallets[item].profit);
                    }
                    else {
                        val[i][j] = val[i+1][j];
                    }
                }
            }
            i++;
        }

        //Outinho::terminal_output(n_pallets,pallets,usedItems);
    }
}

#endif //DYNAMIC_H
