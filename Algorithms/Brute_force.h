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
#include "Utils.h"
#include <limits>
#include <stack>

using namespace std;

namespace Brute_force {
    void run(int capacity, int n_pallets, Pallet *pallets) {

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

        Outinho::terminal_output(n_pallets,pallets,usedItems);

    }
}


/*
void Brute_force::run(int capacity, int n_pallets, Pallet * pallets){


    cout << "Optimal solution using brute force approach: " << endl;

    if (capacity==-1 or n_pallets==-1 or pallets==nullptr){
        cout << "no possible result" << endl;
        return;
    }

    bool usedItems[n_pallets];
    int best_profit=0;
    bool temp_usedItems[n_pallets];

    while () {  // 2^n vezes (todas as combinações possíveis)
        int sum_profits=0;
        int sum_weight=0;
        bool temp_usedItems[n_pallets];
        for (unsigned int b = 0; b < n_pallets; b++) {temp_usedItems[b] = false;} //reset the array

        for (unsigned long int b = 0; b < n_pallets; b++) {
            if (a & (1 << b)) {
                temp_usedItems[b] = true;
                sum_profits += pallets[b].profit;
                sum_weight += pallets[b].weight;
            }

        }
        cout << "sum_profit=" << sum_profits << " sum_weight=" << sum_weight << endl;
        if (sum_weight<=capacity) {
            //cout << "sum_profit=" << sum_profits << " sum_weight=" << sum_weight << endl;
            cout << "best_profit: " << best_profit << endl;
            if (best_profit<sum_profits) {
                best_profit=sum_profits;
                for (unsigned int b = 0; b < n_pallets; b++) {
                    usedItems[b] = false;
                    usedItems[b] = temp_usedItems[b];
                }
            }
        }
    }



    unsigned int last_id=-1;
    for (unsigned int a=n_pallets-1; a>0; a--){
        if (usedItems[a]){
            last_id=a;
            break;
        }
    }

    if (last_id==-1) {
        if (usedItems[0]) last_id=0;
        else cout << "no possible result" << endl;
    }

    int sum_weights=0;
    int sum_profits=0;

    cout << "The pallets used are: (";
    for (unsigned int a=0; a<n_pallets; a++){
        if (a==last_id){
            cout << last_id+1 << ")" << endl;
            sum_weights+=pallets[a].weight;
            sum_profits+=pallets[a].profit;
            break;
        }
        if (usedItems[a]) {
            cout << a+1 << "," ;
            sum_weights+=pallets[a].weight;
            sum_profits+=pallets[a].profit;
        }
    }

    cout << "The total weight used is: " << sum_weights << endl;
    cout << "The best profit is: " << sum_profits << endl;
}*/

#endif //BRUTE_FORCE_H
