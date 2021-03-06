//
//  Inverse_sensitivity.cpp
//  Stage L3
//
//  Created by Alexi Canesse on 07/06/2022.
//

#include "Inverse_sensitivity.hpp"
#include "random.hpp"
#include "exponential_mechanism.hpp"
#include "common_tools.hpp"

#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>

extern class random rdm;

int len_quantile(std::vector<double> &x, double coef_quantile, double goal){
    /* do not pay the sorting part if the db is already sorted */
    if(!std::is_sorted(x.begin(), x.end()))
        std::sort(x.begin(), x.end());
    
    
    auto quantile_it = x.begin() + std::ceil(x.size()*coef_quantile) - 1; /* iterator to the quantile position */
    auto it = quantile_it;
    if(*quantile_it == goal)
        return 0;
    else if(*quantile_it > goal)
        it = upper_bound(x.begin(), x.end(), goal); /* iterator to the first element that is greater than goal, or last if no such element is found. */
    else{
        it = lower_bound(x.begin(), x.end(), goal); /* iterator to the first element that is not less than value, or last if no such element is found. */
        it--;
    }
    
    return (int) std::abs(quantile_it - it) + 1;
}

std::vector<double> inverset_sensitivity(std::vector<double> db, double epsilon){
    /* composition theorem */
    epsilon /= 9;
    
    std::vector<double> result;
    for(int i = 1; i < 10; ++i){
        std::function<double(int)> func = { [i, &db](int j){ return (i*db.size()/10 - j); } };
        
        /* calculate weight of each intervales */
        if(!std::is_sorted(db.begin(), db.end())) /* do not pay the sorting part if the db is already sorted */
            std::sort(db.begin(), db.end());

        std::vector<std::vector<double>> intervales;
        for(int i = 0; i < (int) db.size() - 1; ++i)
            intervales.push_back(std::vector<double>{db.at(i), db.at(i+1), (db.at(i+1) - db.at(i))*std::exp(-func(i)*epsilon/2) });

        
        double normalyzer = 0;
        for(auto x : intervales)
            normalyzer += x.at(2);
        
        for(int i = 0; i < (int) db.size() - 1; ++i)
            intervales.at(i).at(2) /= normalyzer;

        double seed = rdm.Uniforme(0, 1);
        int j = 0;
        while(seed >= 0){
            seed -= intervales.at(j).at(2);
            ++j;
        }
        result.push_back(rdm.Uniforme(intervales.at(j-1).at(0), intervales.at(j-1).at(1)));
        
    }
    
    return result;
}



void test_inverse_sensitivity(int n, double epsilon){
    /*
     * Test inverse sensitivity
     */
    std::vector<double> db = rdm.generate_db(n, [](){ return rdm.Uniforme(0, 1); });
//    double (*func)(double) = +[](double x){ return 1.; };
//    double (*genere)(void) = +[](void){ return rdm.density(+[](double x){ return 0.5*exp(-abs(x)); }, 0.01, -100, 100); };
//    std::vector<double> db = rdm.generate_db(n, genere);
    
    /* composition theorem */
    epsilon /= 9;
    
    std::vector<double> result;
    for(int i = 1; i < 10; ++i){
        std::function<double(double)> func = { [i, &db](double value){ return len_quantile(db, i*0.1, value); } };
        result.push_back(exponential_mechanism(db, 0.001, 0, 1, func, epsilon));
    }

    
    auto real_results = deciles(db);
    std::cout << square_mean_error(result, real_results) << "\n";
    for(int i = 0; i < 9; ++i)
        std::cout << result.at(i) << "         "  << real_results.at(i) << "\n";
}

