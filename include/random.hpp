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
    
    template<typename T, typename... Args>
    std::vector<double> generate_db(int size, T distribution, Args... args);
    random();
    
private:
    unsigned seed;
//    std::random_device rd{};
    std::mt19937_64 gen;
};



#endif /* random_hpp */
