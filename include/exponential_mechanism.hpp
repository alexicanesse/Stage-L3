//
//  exponential_mechanism.hpp
//  Stage L3
//
//  Created by Alexi Canesse on 09/06/2022.
//

#ifndef exponential_mechanism_hpp
#define exponential_mechanism_hpp

#include <stdio.h>
#include <vector>
#include <functional>

double exponential_mechanism(std::vector<double> &x, double precision, double a, double b, std::function<double(double)>, double epsilon);

#endif /* exponential_mechanism_hpp */
