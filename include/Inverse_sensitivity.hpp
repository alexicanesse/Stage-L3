//
//  Inverse_sensitivity.hpp
//  Stage L3
//
//  Created by Alexi Canesse on 07/06/2022.
//

#ifndef Inverse_sensitivity_hpp
#define Inverse_sensitivity_hpp

#include <stdio.h>
#include <vector>

int len_quantile(std::vector<double> &x, double coef_quantile, double goal);

void test_inverse_sensitivity(int n, double epsilon);

#endif /* Inverse_sensitivity_hpp */
