//
// Created by Lenovo on 20/04/2025.
//

#ifndef BRUTE_FORCE_H
#define BRUTE_FORCE_H

#include <iostream>
#include <vector>
#include "../parse/Pallet.h"
#include "Outinho.h"
#include <chrono>
#include <limits>
#include <stack>

using namespace std;

/**
 * @namespace Brute_force
 * @brief This namespace is responsible for implementing the
 * brute force and backtracking approaches
 *
 */
namespace Brute_force {


    /**
     * @brief brute force approach to the problem
     *
     * @param capacity the maximum weight of the pallets
     * @param n_pallets the number of pallets
     * @param pallets pointer to object Pallet
     * @return void
     */
    void runBruteForce(int capacity, int n_pallets, Pallet *pallets) {
        auto start = std::chrono::high_resolution_clock::now();

        cout << "Optimal solution using brute force approach: " << endl;

        if (capacity==-1 or n_pallets==-1 or pallets==nullptr){
            cout << "no possible result" << endl;
            return;
        }

        bool tempUsedItems[n_pallets];
        bool usedItems[n_pallets];
        unsigned int res = 0;
        unsigned int resWeights = 9999999;

        for (unsigned int i = 0; i < n_pallets; i++) {
            tempUsedItems[i] = 0;
        }
        bool flag = true;
        while (flag) {
            auto current = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::seconds>(current - start);
            if (duration>=std::chrono::seconds(20)) {
                cout << "Too much time! It took more than 20 seconds! Choose another algorithm!" << endl;
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
            if (sum_weights <= capacity ) {
                if (sum_profits > res || (sum_profits == res && sum_weights < resWeights)) {
                    resWeights = sum_weights;
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



    /**
     * @brief recursive auxiliary function to
     * the backtracking approach
     *
     * @param k the index of the item that is being
     * analised in this function call
     * @param capacity the maximum weight of the pallets
     * @param n_pallets the number of pallets
     * @param pallets pointer to object Pallet
     * @param tempUsedItems temporary array with
     * what items are being used
     * @param sum_weight current sum of the weights
     * @param sum_profit current sum of the profits
     * @param best_profit best profit yet
     * @param best_weight sum of the weights
     * to obtain the best profit yet
     * @param bestUsedItems array with what
     * items are being used in the best solution yet
     * @param flag identify if algorithm exceeded time
     * @param start start time of the algorithm
     * @return void
     */
    void recursiveBacktracking(unsigned int k, int capacity, int n_pallets, Pallet *pallets, bool tempUsedItems[],
        unsigned int sum_weight, unsigned int sum_profit, unsigned int & best_profit, unsigned int & best_weight,bool bestUsedItems[],bool & flag,std::chrono::time_point<std::chrono::high_resolution_clock> start) {

        auto current = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(current - start);
        if (duration>=std::chrono::seconds(20)) {
            flag = true;
            return;
        }


        if (tempUsedItems[k]) {
            sum_weight += pallets[k].weight;
            sum_profit += pallets[k].profit;
        }

        if (sum_weight>capacity ) {
            return;
        }


        if (sum_profit>best_profit || (sum_profit == best_profit && sum_weight < best_weight)) {
            best_profit = sum_profit;
            best_weight = sum_weight;
            for (unsigned int i = 0; i < n_pallets; i++) {
                bestUsedItems[i] = tempUsedItems[i];
            }
        }

        k++;
        if (k == n_pallets) return;


        tempUsedItems[k] = 1;
        recursiveBacktracking(k,capacity,n_pallets,pallets,tempUsedItems,sum_weight,sum_profit,best_profit,best_weight,bestUsedItems,flag,start);

        tempUsedItems[k] = 0;

        recursiveBacktracking(k,capacity,n_pallets,pallets,tempUsedItems,sum_weight,sum_profit,best_profit,best_weight,bestUsedItems,flag,start);

    }




    /**
     * @brief backtracking approach
     * @param capacity the maximum weight of the pallets
     * @param n_pallets the number of pallets
     * @param pallets pointer to object Pallet
     * @return void
     */
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
        bool flag=false;

        recursiveBacktracking(k,capacity,n_pallets,pallets,tempUsedItems,sum_weight,sum_profit,best_profit,best_weight,usedItems,flag,start);


        if (flag) {
            cout << "Too much time! It took more than 20 seconds! Choose another algorithm!" << endl;
            return;
        }


        tempUsedItems[k] = 0;

        recursiveBacktracking(k,capacity,n_pallets,pallets,tempUsedItems,sum_weight,sum_profit,best_profit,best_weight,usedItems,flag,start);

        if (flag) {
            cout << "Too much time! It took more than 20 seconds! Choose another algorithm!" << endl;
            return;
        }

        auto end = std::chrono::high_resolution_clock::now();

        Outinho::terminal_output(n_pallets,pallets,usedItems,start, end);
    }
}



#endif //BRUTE_FORCE_H
