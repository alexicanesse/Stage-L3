//
//  random.cpp
//  Stage L3
//
//  Created by Alexi Canesse on 08/06/2022.
//

#include "random.hpp"

#include <algorithm>
#include <random>
#include <chrono>
#include <functional>


random::random(){
    this->seed = std::chrono::system_clock::now().time_since_epoch().count();
    this->gen = std::mt19937_64(seed);
}

double random::Laplace(double b){
    std::exponential_distribution<double> d(b);
    std::uniform_int_distribution<int> sign(0,1);

    return 0.5*d(this->gen)*pow((-1), sign(this->gen));
}


double random::Uniforme(double a, double b){
    std::uniform_real_distribution<double> d(a, b);
    return d(this->gen);
}

std::vector<double> random::generate_db(int size, double (*random_val)(void)){
    std::vector<double> db;
    
    for(int i = 0; i < size; ++i)
        db.push_back(random_val());
    
    return db;
}

double random::density(std::function<double(double)> density_func, double precision, double a, double b){
    double seed = this->Uniforme(0, 1);
    double a_init = a;
    /* we will return x such that P(X <= x) == seed */
    while(b-a > precision){
        if(seed < numericIntegration(density_func, a_init, (a+b)/2, precision))
            b = (a+b)/2;
        else
            a = (a+b)/2;
    }
    return (a+b)/2;
}


double numericIntegration(std::function<double(double)> func, double a, double b, double epsilon){
    double x = a;
    
    double result = 0;
    while(x <= b){
        result += func(x) * epsilon;
        x += epsilon;
    }
    
    return result;
}
