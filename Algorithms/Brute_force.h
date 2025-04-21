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

class Brute_force{
  public:
    Brute_force(){}
    void run(int capacity, int n_pallets, Pallet * pallets);
};


void Brute_force::run(int capacity, int n_pallets, Pallet * pallets){


    cout << "Optimal solution using brute force approach: " << endl;

    if (capacity==-1 or n_pallets==-1 or pallets==nullptr){
        cout << "no possible result" << endl;
        return;
    }

    bool usedItems[n_pallets];
    int best_profit=0;
    for (unsigned int a = 0; a < (1<<n_pallets); a++) {  // 2^n vezes (todas as combinações possíveis)
        int sum_profits=0;
        int sum_weight=0;
        bool temp_usedItems[n_pallets];
        for (unsigned int b = 0; b < n_pallets; b++) {temp_usedItems[b] = false;} //reset the array

        for (unsigned int b = 0; b < n_pallets; b++) {
            if (a & (1 << b)) {
                temp_usedItems[b] = true;
                sum_profits += pallets[b].profit;
                sum_weight += pallets[b].weight;
            }
        }
        if (sum_weight<=capacity) {
            if (best_profit<sum_profits) {
                best_profit=sum_profits;
                for (unsigned int b = 0; b < n_pallets; b++) {usedItems[b] = false;}
                for (unsigned int b = 0; b < n_pallets; b++) {usedItems[b] = temp_usedItems[b];}
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

    cout << "The pallets used are: (";
    for (int a=0; a<n_pallets; a++){
        if (a==last_id){
            cout << last_id+1 << ")" << endl;
            break;
        }
        if (usedItems[a]) cout << a+1 << "," ;
    }

}

#endif //BRUTE_FORCE_H
