//
// Created by Lenovo on 24/04/2025.
//

#ifndef GREEDY_H
#define GREEDY_H

#include <iostream>
#include <vector>
#include "../data_structures/Graph.h"
#include "../parse/Pallet.h"
#include "Outinho.h"
#include "Utils.h"
#include <limits>
#include <stack>
#include <algorithm>

using namespace std;

namespace Greedy {
    void run(int capacity, int n_pallets, Pallet * pallets){

        cout << "Optimal solution using Greedy approach: "<< endl;

        if (capacity==-1 or n_pallets==-1 or pallets==nullptr){
            cout << "no possible result" << endl;
            return;
        }

        bool usedItems[n_pallets]={false};

        vector<pair<double, unsigned int>> v;
        for (unsigned int i = 0; i < n_pallets; i++) {
            v.push_back({(double)pallets[i].profit/pallets[i].weight,i});
        }
        sort(v.begin(), v.end(), [](const pair<double, unsigned int>& p1, const pair<double, unsigned int>& p2) {return p1.first > p2.first;});
        int weight = 0;
        int res = 0;
        for (unsigned int i = 0; i < n_pallets; i++) {
            if (weight + pallets[v[i].second].weight <= capacity) {
                weight += pallets[v[i].second].weight;
                res += pallets[v[i].second].profit;
                usedItems[v[i].second] = true;
            }
        }

        Outinho::terminal_output(n_pallets,pallets,usedItems);
    }
}

#endif //GREEDY_H
