//
//  random.hpp
//  Stage L3
//
//  Created by Alexi Canesse on 08/06/2022.
//

#ifndef random_hpp
#define random_hpp

#include <stdio.h>
#include <random>
#include <vector>

class random{
public:
    double Laplace(double b);
    double Uniforme(double a, double b);
    double density(double (*density_func)(double x), double precision, double a, double b);
    
    std::vector<double> generate_db(int size, double (*random_val)(void));
    random();
    
private:
    long long seed;
    std::mt19937_64 gen;
};


double numericIntegration(double (*func)(double x), double a, double b, double epsilon); //integrate func on [a,b]


#endif /* random_hpp */
