//
//  myrtille.cpp
//  Stage L3
//
//  Created by Alexi Canesse on 10/06/2022.
//

#include "myrtille.hpp"
#include "AboveThreshold.hpp"
#include "random.hpp"
#include "common_tools.hpp"

#include <functional>
#include <iostream>

extern class random rdm;

double linear_quintille_using_threashold(std::vector<double> &db, double a, double b, double coef_quintille, double epsilon){
    double a_copy = a;
    double n = db.size();
    int steps = 1.5*n/log(n);
    
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

std::vector<double> myrtille(std::vector<double> db, double epsilon, double a, double b){
    /* composition theorem */
    epsilon /= 9;
    
    std::vector<double> result;
    for(int i = 1; i < 10; ++i)
        result.push_back(linear_quintille_using_threashold(db, a, b, 0.1*i, epsilon));
    
    return result;
}

//void test_myrtille(int n, int steps, double epsilon){
//    /*
//     * Test myrtille
//     */
//    std::vector<double> db = rdm.generate_db(n, [](){ return rdm.Uniforme(0., 1.); });
//
//    /* composition theorem */
//    epsilon /= 9;
//
//    std::vector<double> err;
//    int i = 100;
//    while(i--){
//        std::vector<double> result;
//        for(int i = 1; i < 10; ++i)
//            result.push_back(linear_quintille_using_threashold(db, steps, -1, 1, 0.1*i, epsilon));
//        auto real_results = deciles(db);
//        for(int j = 0; j < 9; ++j)
//            err.push_back(abs(result.at(j) - real_results.at(j)));
//    }
//
//
//
//    std::cout << mean_10(err) << "\n";
//}
