//
//  random.cpp
//  Stage L3
//
//  Created by Alexi Canesse on 08/06/2022.
//

#include "random.hpp"

#include <algorithm>
#include <random>


random::random(){
    this->gen = std::mt19937{rd()};
}

double random::Laplace(double b){
    std::exponential_distribution<float> d(b);
    std::uniform_int_distribution sign(0,1);

    return 0.5*d(this->gen)*pow((-1), sign(this->gen));
}


double random::Uniforme(double a, double b){
    std::uniform_real_distribution d(a, b);
    return d(this->gen);
}


template<typename T, typename... Args>
std::vector<double> random::generate_db(int size, T distribution, Args... args){
    std::vector<double> db;
    
    for(int i = 0; i < size; ++i)
        db.push_back(*T(args...));
    
    return db;
}
