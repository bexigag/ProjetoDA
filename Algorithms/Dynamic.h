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
#include "Utils.h"
#include <limits>
#include <stack>

using namespace std;

class Dynamic{
public:
    Dynamic(){}
    void run(int capacity, int n_pallets, Pallet * pallets);
};

void Dynamic::run(int capacity, int n_pallets, Pallet * pallets){

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

    bool usedItems[n_pallets];
    for (unsigned int i = 0; i <= n_pallets; i++) {usedItems[i] = false;}

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
}

#endif //DYNAMIC_H
