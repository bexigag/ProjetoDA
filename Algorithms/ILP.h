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
#include <limits>
#include <chrono>
#include <stack>
#include "Outinho.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <string>

using namespace std;

namespace ILP {
    void runILP(int capacity, int n_pallets, Pallet* pallets) {
    auto start = chrono::high_resolution_clock::now();

    if (capacity < 0 || n_pallets < 0 || pallets == nullptr) {
        cout << "no possible result" << endl;
        return;
    }

    // 1. Escrever o input.txt
    ofstream input("input.txt");
    input << "capacity " << capacity << "\n";
    input << "values";
    for (int i = 0; i < n_pallets; ++i)
        input << " " << pallets[i].profit;
    input << "\nweights";
    for (int i = 0; i < n_pallets; ++i)
        input << " " << pallets[i].weight;
    input << endl;
    input.close();

    // 2. Chamar o script Python
    int result = system("python knapsack_solver.py input.txt output.txt");
    if (result != 0) {
        cerr << "Error running knapsack_solver.py" << endl;
        return;
    }

    // 3. Ler o output.txt
    bool usedItems[n_pallets] = { false };  // inicia todos a false
    ifstream output("output.txt");
    string label;
    output >> label; // "selected_items"
    for (int i = 0; i < n_pallets && output; ++i) {
        int flag;
        output >> flag;
        usedItems[i] = (flag == 1);
    }

    // Ler "total_value ..." (ignorado aqui, mas pode ser usado)
    output >> label; // "total_value"
    int totalValue;
    output >> totalValue;
    output.close();

    auto end = chrono::high_resolution_clock::now();

    cout << "Optimal solution using ILP approach: " << endl;

    // 4. Mostrar resultado
    Outinho::terminal_output(n_pallets, pallets, usedItems, start, end);
}

}

#endif //ILP_H
