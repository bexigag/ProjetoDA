//
// Created by gonca on 22/05/2025.
//

#ifndef BESTOPTION_H
#define BESTOPTION_H


#include <iostream>
#include <string>
#include "../parse/parse.h"
#include <cmath>
#include "../parse/Pallet.h"
#include "../Algorithms/Brute_force.h"
#include "../Algorithms/Dynamic.h"
#include "../Algorithms/Greedy.h"
#include "../Algorithms/ILP.h"
#include "../Algorithms/Outinho.h"


using namespace std;

/**
 * @namespace bestoption
 * @brief This namespace is responsible for implementing the
 * algorithm of the project with the lowest execution time
 *
 */
namespace bestoption{



    /**
     * @brief chooses the right algorithm accordingly to the input provided
     *
     * @param capacity the maximum weight of the pallets
     * @param n_pallets the number of pallets
     * @param pallets pointer to object Pallet
     * @return void
     */
    void runBestOption(int capacity, int n_pallets, Pallet *pallets){
        double brute_force = n_pallets;
        double dynamic = log2(capacity)+log2(n_pallets);

        if (brute_force > dynamic) {
            Dynamic::runDynamic(capacity, n_pallets, pallets);
        }

        else {
            Brute_force::run_backtracking(capacity, n_pallets, pallets);
        }
    }

}



#endif //BESTOPTION_H
