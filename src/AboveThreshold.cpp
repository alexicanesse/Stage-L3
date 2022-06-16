//
//  AboveThreshold.cpp
//  Stage L3
//
//  Created by Alexi Canesse on 10/06/2022.
//

#include "AboveThreshold.hpp"
#include "random.hpp"

#include <functional>
#include <vector>

extern class random rdm;

int AboveThreshold(std::vector<double> &db, std::vector<std::function<double(std::vector<double>&)>> f, double T, double epsilon){
    int i = 0;
    
    T += rdm.Laplace(2/epsilon);
    for(auto fi : f){
        double vi = rdm.Laplace(4/epsilon);
        if(fi(db) + vi > T)
            return i;
        i++;
    }
    return -1;
}


