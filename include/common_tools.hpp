//
//  common_tools.hpp
//  Stage L3
//
//  Created by Alexi Canesse on 09/06/2022.
//

#ifndef common_tools_hpp
#define common_tools_hpp

#include <stdio.h>
#include <vector>

std::vector<double> deciles(std::vector<double> &db);
std::vector<double> deciles_sorted(std::vector<double> &db);
double decile(std::vector<double> &db, int which);
double decile_sorted(std::vector<double> &db, int which);

double mean_10(std::vector<double> &data);
double square_mean_error(std::vector<double> &t1, std::vector<double> &t2);

#endif /* common_tools_hpp */
