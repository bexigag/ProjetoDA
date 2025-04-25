//
// Created by gonca on 27/03/2025.
//

#ifndef OUTINHO_H
#define OUTINHO_H

#include "../data_structures/Graph.h"
#include "../parse/Pallet.h"

namespace Outinho {
    void terminal_output(int n_pallets, Pallet *pallets, bool usedItems[]) {
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
}

#endif //OUTINHO_H
