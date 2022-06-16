//
//  myrtille.hpp
//  Stage L3
//
//  Created by Alexi Canesse on 10/06/2022.
//

#ifndef myrtille_hpp
#define myrtille_hpp

#include <stdio.h>
#include <vector>


double linear_quintille_using_threashold(std::vector<double> &db, int steps, double a, double b, double coef_quintille, double epsilon);

void test_myrtille(int n, int steps, double epsilon);

#endif /* myrtille_hpp */
