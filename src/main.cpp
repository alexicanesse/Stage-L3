//
//  main.cpp
//  Stage L3
//
//  Created by Alexi Canesse on 07/06/2022.
//
#include <iostream>

#include "Subsample_and_aggregate.hpp"
#include "Inverse_sensitivity.hpp"
#include "random.hpp"

class random rdm;

int main(int argc, const char * argv[]) {
//    test_deciles_subsample_and_aggregate(100000, 10000, 1, 0);
//    std::vector<float> db = {0, 1, 2, 3, 4};
//    std::cout << len_quantile(db, 0.5, -1);
    test_inverse_sensitivity(1000, 1);
    return 0;
}
