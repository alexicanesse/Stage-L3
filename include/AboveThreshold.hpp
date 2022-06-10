//
//  AboveThreshold.hpp
//  Stage L3
//
//  Created by Alexi Canesse on 10/06/2022.
//

#ifndef AboveThreshold_hpp
#define AboveThreshold_hpp

#include <vector>
#include <stdio.h>
#include <functional>

int AboveThreshold(std::vector<double> &db, std::vector<std::function<double(std::vector<double>&)>> f, double T, double epsilon);
#endif /* AboveThreshold_hpp */
