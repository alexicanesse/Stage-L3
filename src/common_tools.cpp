//
//  common_tools.cpp
//  Stage L3
//
//  Created by Alexi Canesse on 09/06/2022.
//

#include "common_tools.hpp"

#include <cmath>
#include <algorithm>

std::vector<double> deciles(std::vector<double> &db){
    std::vector<double> db_copy = db;
    std::sort(db_copy.begin(), db_copy.end());
    
    return deciles_sorted(db_copy);
}

std::vector<double> deciles_sorted(std::vector<double> &db){
    std::vector<double> result;
    for(int i = 1; i < 10; ++i){
        result.push_back(db.at(i * ((int) db.size() / 10)));
    }
    
    return result;
}

double decile(std::vector<double> &db, int which){
    std::vector<double> db_copy = db;
    std::sort(db_copy.begin(), db_copy.end());
    
    return decile_sorted(db_copy, which);
}

double decile_sorted(std::vector<double> &db, int which){
    return db.at(which * ((int) db.size() / 10));
}

double mean_10(std::vector<double> &data){
    double sum = 0;
    for(int i = (int) data.size() / 10; i < (int) data.size() - (int) data.size() / 10; ++i)
        sum += data.at(i);
    
    
    return sum/(data.size() - 2*((int) data.size() / 10));
}

double square_mean_error(std::vector<double> &t1, std::vector<double> &t2){
    double sum = 0;
    for(int i = 0; i < (int) t1.size(); ++i)
        sum += pow((t1.at(i) - t2.at(i)), 2);
    
    return sqrt(sum/t1.size());
}

