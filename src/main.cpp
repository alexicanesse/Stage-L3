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
//    test_deciles_subsample_and_aggregate(100000, 10000, 1, 0);
//    std::vector<float> db = {0, 1, 2, 3, 4};
//    std::cout << len_quantile(db, 0.5, -1);
//    test_inverse_sensitivity(1000, 1);
//    test_myrtille(1000, 100000, 1);
//    myrtille_against_inverse_sensitivity_graph_uniforme(20, 1);
    
    
//    double gamma = 0.01;
//    int k = 1000;
//    double beta = 0.1;
//    double epsilon = 1;
//    double alpha = 8*(log(k) + log(2/beta))/epsilon;
//    int n = 10000;
//    std::cout << alpha << "\n";
//    double mu = 0;
//
//    for(int j = 0; j < alpha; ++j){
//        mu += binomialCoefficients(n, j) * pow(gamma/2, j) * pow(1 - gamma/2, n-j);
//    }
//
//
//    mu *= 2;
//    std::cout << mu << "\n";
//    test_myrtille(10000, 1000, 1);
//    real_data_graph();
//    smooting("./raw_data/fig2");
//    uniform_graph();
//    light_version("./raw_data/fig3_1.000000");
//    normale_graph();
//    light_version("./raw_data/fig4_1.000000");
    
    output_graphe_borne_esperance();
    return 0;
}
