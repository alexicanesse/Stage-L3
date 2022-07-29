//
//  main.cpp
//  Stage L3
//
//  Created by Alexi Canesse on 07/06/2022.
//
#include <iostream>
#include <math.h>

#include "Subsample_and_aggregate.hpp"
#include "Inverse_sensitivity.hpp"
#include "random.hpp"
#include "myrtille.hpp"
#include "comparaisons.hpp"

class random rdm;

double fact(int n){
    if(n == 0) return 1;
    return n*fact(n-1);
}

u_int64_t binomialCoefficients(int n, int k) {
    return floor(fact(n)/(fact(k)*fact(n-k)));
}

int main(int argc, const char * argv[]) {

    return 0;
}
