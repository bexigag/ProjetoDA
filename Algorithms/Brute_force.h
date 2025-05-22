//
// Created by Lenovo on 20/04/2025.
//

#ifndef BRUTE_FORCE_H
#define BRUTE_FORCE_H

#include <iostream>
#include <vector>
#include "../data_structures/Graph.h"
#include "../parse/Pallet.h"
#include "Outinho.h"
#include <chrono>
#include "Utils.h"
#include <limits>
#include <stack>

using namespace std;

namespace Brute_force {
    void run(int capacity, int n_pallets, Pallet *pallets) {
        auto start = std::chrono::high_resolution_clock::now();

        cout << "Optimal solution using brute force approach: " << endl;

        if (capacity==-1 or n_pallets==-1 or pallets==nullptr){
            cout << "no possible result" << endl;
            return;
        }

        bool tempUsedItems[n_pallets];
        bool usedItems[n_pallets];
        unsigned int res = 0;
        for (unsigned int i = 0; i < n_pallets; i++) {
            tempUsedItems[i] = 0;
        }
        bool flag = true;
        while (flag) {
            auto current = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::seconds>(current - start);
            if (duration>=std::chrono::seconds(10)) {
                cout << "Too much time! It took more than 10 seconds! Choose another algorithm!" << endl;
                return;
            }
            flag = false;
            for (unsigned int i = 0; i < n_pallets; i++) {
                if (tempUsedItems[i] == 0) {
                    tempUsedItems[i] = 1;
                    for (unsigned int j = 0; j < i; j++) {
                        tempUsedItems[j] = 0;
                    }
                    flag = true;
                    break;
                }
            }

            unsigned int sum_profits = 0;
            unsigned int sum_weights = 0;
            for (unsigned int i = 0; i < n_pallets; i++) {
                if (tempUsedItems[i]) {
                    sum_weights += pallets[i].weight;
                    sum_profits += pallets[i].profit;
                }
            }
            if (sum_weights <= capacity) {
                if (sum_profits > res) {
                    res = sum_profits;
                    for (unsigned int i = 0; i < n_pallets; i++) {
                        usedItems[i] = tempUsedItems[i];
                    }
                }
            }

        }

        auto end = std::chrono::high_resolution_clock::now();



        Outinho::terminal_output(n_pallets,pallets,usedItems, start, end);

    }

    void recursiveBacktracking(unsigned int k, int capacity, int n_pallets, Pallet *pallets, bool tempUsedItems[],
        unsigned int sum_weight, unsigned int sum_profit, unsigned int & best_profit, unsigned int & best_weight,bool bestUsedItems[], auto start) {

        auto current = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(current - start);
        if (duration>=std::chrono::seconds(10)) {
            cout << "Too much time! It took more than 10 seconds! Choose another algorithm!" << endl;
            return;
        }

        if (tempUsedItems[k]) {
            sum_weight += pallets[k].weight;
            sum_profit += pallets[k].profit;
        }

        if (sum_weight>capacity ) {
            return;
        }


        if (sum_profit>best_profit) {
            best_profit = sum_profit;
            best_weight = sum_weight;
            for (unsigned int i = 0; i < n_pallets; i++) {
                bestUsedItems[i] = tempUsedItems[i];
            }
        }

        k++;
        if (k == n_pallets) return;


        tempUsedItems[k] = 1;
        recursiveBacktracking(k,capacity,n_pallets,pallets,tempUsedItems,sum_weight,sum_profit,best_profit,best_weight,bestUsedItems,start);

        tempUsedItems[k] = 0;

        recursiveBacktracking(k,capacity,n_pallets,pallets,tempUsedItems,sum_weight,sum_profit,best_profit,best_weight,bestUsedItems,start);

    }

    void run_backtracking(int capacity, int n_pallets, Pallet *pallets) {

        auto start = std::chrono::high_resolution_clock::now();

        cout << "Optimal solution using brute force with backtracking approach: " << endl;

        if (capacity==-1 or n_pallets==-1 or pallets==nullptr){
            cout << "no possible result" << endl;
            return;
        }

        bool tempUsedItems[n_pallets];
        bool usedItems[n_pallets];
        for (unsigned int i = 0; i < n_pallets; i++) {
            tempUsedItems[i] = false;
        }


        unsigned int sum_weight=0, sum_profit=0, best_profit=0,best_weight=0,k=0;

        tempUsedItems[k] = 1;

        recursiveBacktracking(k,capacity,n_pallets,pallets,tempUsedItems,sum_weight,sum_profit,best_profit,best_weight,usedItems,start);

        tempUsedItems[k] = 0;

        recursiveBacktracking(k,capacity,n_pallets,pallets,tempUsedItems,sum_weight,sum_profit,best_profit,best_weight,usedItems,start);

        auto end = std::chrono::high_resolution_clock::now();

        Outinho::terminal_output(n_pallets,pallets,usedItems,start, end);
    }
}



#endif //BRUTE_FORCE_H
