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

namespace bestoption{

    void runBestOption(int capacity, int n_pallets, Pallet *pallets){
        double brute_force = log(2) *n_pallets;
        double dynamic = log(capacity)+log(n_pallets);

        if (brute_force > dynamic) {
            Dynamic::runDynamic(capacity, n_pallets, pallets);
        }

        else {
            Brute_force::runBruteForce(capacity, n_pallets, pallets);
        }
    }

}



#endif //BESTOPTION_H
