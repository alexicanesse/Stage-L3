//
//  exponential_mechanism.cpp
//  Stage L3
//
//  Created by Alexi Canesse on 09/06/2022.
//

#include <vector>
#include <functional>

#include "exponential_mechanism.hpp"
#include "random.hpp"

extern class random rdm;

double exponential_mechanism(std::vector<double> &x, double precision, double a, double b, std::function<double(double)> func, double epsilon){
    std::function<double(double)> integrate = { [epsilon, func](double x){
        return exp(-func(x)*epsilon/2);
    } };
    double normalyzer = numericIntegration(integrate, a, b, precision);
    
    integrate = { [epsilon, func, normalyzer](double x){
        return exp(-func(x)*epsilon/2)/normalyzer;
    } };
    return rdm.density(integrate, precision, a, b);
}

