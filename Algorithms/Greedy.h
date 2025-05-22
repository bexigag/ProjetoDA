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
#include <chrono>
#include <limits>
#include <stack>
#include <algorithm>

using namespace std;

namespace Greedy {
    void runDensity(int capacity, int n_pallets, Pallet * pallets){

        auto start = std::chrono::high_resolution_clock::now();

        cout << "Optimal solution using Greedy approach by Density: "<< endl;

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
            auto current = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::seconds>(current - start);
            if (duration>=std::chrono::seconds(20)) {
                cout << "Too much time! It took more than 20 seconds! Choose another algorithm!" << endl;
                return;
            }
            if (weight + pallets[v[i].second].weight <= capacity) {
                weight += pallets[v[i].second].weight;
                res += pallets[v[i].second].profit;
                usedItems[v[i].second] = true;
            }
        }

        auto end = std::chrono::high_resolution_clock::now();

        Outinho::terminal_output(n_pallets,pallets,usedItems,start, end);
    }

    void runValue(int capacity, int n_pallets, Pallet * pallets){
        auto start = std::chrono::high_resolution_clock::now();

        cout << "Optimal solution using Greedy approach by Value: "<< endl;

        if (capacity==-1 or n_pallets==-1 or pallets==nullptr){
            cout << "no possible result" << endl;
            return;
        }

        bool usedItems[n_pallets]={false};
        vector<Pallet> v;
        for (unsigned int i = 0; i < n_pallets; i++) {
            v.push_back(pallets[i]);
        }

        sort(v.begin(), v.end(), [](const Pallet& p1, const Pallet& p2) {return p1.profit > p2.profit;});
        int weight = 0;
        int res = 0;
        for (unsigned int i = 0; i < n_pallets; i++) {
            auto current = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::seconds>(current - start);
            if (duration>=std::chrono::seconds(20)) {
                cout << "Too much time! It took more than 20 seconds! Choose another algorithm!" << endl;
                return;
            }
            if (weight + v[i].weight<= capacity) {
                weight += v[i].weight;
                res += v[i].profit;
                usedItems[v[i].id - 1] = true;
            }
        }

        auto end = std::chrono::high_resolution_clock::now();

        Outinho::terminal_output(n_pallets,pallets,usedItems,start, end);
    }

    void run2Aproximation(int capacity, int n_pallets, Pallet * pallets){

        cout << "Optimal solution using 2 Aproximation (Best of Greedy): "<< endl;

        auto start = std::chrono::high_resolution_clock::now();


        if (capacity==-1 or n_pallets==-1 or pallets==nullptr){
            cout << "no possible result" << endl;
            return;
        }

        bool usedItemsValue[n_pallets]={false};
        vector<Pallet> v;
        for (unsigned int i = 0; i < n_pallets; i++) {
            v.push_back(pallets[i]);
        }

        sort(v.begin(), v.end(), [](const Pallet& p1, const Pallet& p2) {return p1.profit > p2.profit;});
        int weight = 0;
        int resValue = 0;
        for (unsigned int i = 0; i < n_pallets; i++) {
            if (weight + v[i].weight<= capacity) {
                weight += v[i].weight;
                resValue += v[i].profit;
                usedItemsValue[v[i].id - 1] = true;
            }
        }

        bool usedItemsDensity[n_pallets]={false};

        vector<pair<double, unsigned int>> v2;
        for (unsigned int i = 0; i < n_pallets; i++) {
            v2.push_back({(double)pallets[i].profit/pallets[i].weight,i});
        }
        sort(v2.begin(), v2.end(), [](const pair<double, unsigned int>& p1, const pair<double, unsigned int>& p2) {return p1.first > p2.first;});
        weight = 0;
        int resDensity = 0;
        for (unsigned int i = 0; i < n_pallets; i++) {
            if (weight + pallets[v2[i].second].weight <= capacity) {
                weight += pallets[v2[i].second].weight;
                resDensity += pallets[v2[i].second].profit;
                usedItemsDensity[v2[i].second] = true;
            }
        }


        auto end = std::chrono::high_resolution_clock::now();

        if (resValue > resDensity) {
            cout << "Using Greedy by Value approach:" << endl;
            Outinho::terminal_output(n_pallets,pallets,usedItemsValue,start, end);
        }
        else {
            cout << "Using Greedy by Density approach:" << endl;
            Outinho::terminal_output(n_pallets,pallets,usedItemsDensity,start, end);
        }

    }

}

#endif //GREEDY_H
