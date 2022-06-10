//
//  myrtille.cpp
//  Stage L3
//
//  Created by Alexi Canesse on 10/06/2022.
//

#include "myrtille.hpp"
#include "AboveThreshold.hpp"

#include <functional>

double linear_quintille_using_threashold(std::vector<double> &db, int steps, double a, double b, double coef_quintille, double epsilon){
    double a_copy = a;
    
    /* create the queries */
    double lambda = (b-a)/steps;
    std::vector<std::function<double(std::vector<double> &)>> Q;
    while(steps--){
        std::function<double(std::vector<double> &)> fi = { [a](std::vector<double> &db){
            int count = 0;
            for(auto e : db){
                if(e < a)
                    count++;
            }
            
            return count;
        } };
        
        a += lambda;
        Q.push_back(fi);
    }
    
    return a_copy + AboveThreshold(db, Q, coef_quintille*db.size(), epsilon)*lambda;
}
