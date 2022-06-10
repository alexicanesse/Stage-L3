//
//  Subsample_and_aggregate.cpp
//  Stage L3
//
//  Created by Alexi Canesse on 07/06/2022.
//

#include "Subsample_and_aggregate.hpp"
#include "random.hpp"
#include "common_tools.hpp"

#include <algorithm>
#include <random>
#include <iostream>
#include <vector>
#include <functional>

extern class random rdm;

Subsample_and_aggregate::Subsample_and_aggregate(std::vector<double> (*to_compute)(std::vector<double>&), std::vector<double> (*Aggregate)(std::vector<std::vector<double>>, double delta_agg, double epsilon), std::vector<double> db, int number_of_partition, double epsilon, double delta, double delta_agg){
    this->to_compute = to_compute;
    this->Aggregate = Aggregate;
    this->db = db;
    this->number_of_partition = number_of_partition;
    this->epsilon = epsilon;
    this->delta = delta;
    this->delta_agg = delta_agg;
}

std::vector<double> Subsample_and_aggregate::get_result(){
    std::vector<std::vector<double>> samples = this->randomly_partition();
    
    std::vector<std::vector<double>> computed;
    for(auto sample : samples)
        computed.push_back(this->to_compute(sample));
    
    return this->Aggregate(computed, this->delta_agg, this->epsilon);
}

std::vector<std::vector<double>> Subsample_and_aggregate::randomly_partition(){
    std::vector<double> db_copy = this->db;
    
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(db_copy.begin(), db_copy.end(), g);
    
    
    std::vector<std::vector<double>> result;
    int pos = 0;
    for(int i = 0; i < this->number_of_partition; ++i){
        std::vector<double> buff;
        
        int size = (int) db_copy.size() / this->number_of_partition;
        if(i < ((int) db_copy.size() % this->number_of_partition)) /* distribute the value that does not fit */
            size += 1;
        
        
        for(int j = 0; j < size; ++j)
            buff.push_back(db_copy.at(pos++));
        
        
                           
        result.push_back(buff);
    }
        
    return result;
}




std::vector<double> Aggregate_10_mean(std::vector<std::vector<double>> samples_computed, double delta_agg, double epsilon){
    std::vector<std::vector<double>> computed_vals(samples_computed.at(0).size());
    
    std::vector<double> result;
    for(auto e : samples_computed)
        for(int i = 0; i < (int) e.size(); ++i)
            computed_vals.at(i).push_back(e.at(i));
    
    for(auto e : computed_vals){
        result.push_back(mean_10(e) + rdm.Laplace(1./(delta_agg/epsilon)));
    }
    return result;
}


void test_deciles_subsample_and_aggregate(int n, int k, double epsilon, double delta){
    /*
     * Test subsample and aggregate
     */
    std::vector<double> db = rdm.generate_db(n, [](){ return rdm.Uniforme(0., 1.); });
//    double (*func)(double) = +[](double x){ return 1.; };
//    double (*genere)(void) = +[](void){ return rdm.density(+[](double x){ return 0.5*exp(-abs(x)); }, 0.01, -100, 100); };
//    std::vector<double> db = rdm.generate_db(n, genere);

    /* composition theorem */
    if(delta != 0)
        epsilon /= 2*sqrt(2*9*log(1./delta));
    else
        epsilon /= 9;


    Subsample_and_aggregate sa(&deciles, &Aggregate_10_mean, db, k, epsilon, delta, 1./k);
    auto result(sa.get_result());
    auto real_results = deciles(db);
    std::cout << square_mean_error(result, real_results);
//    for(auto e : db)
//        std::cout << e << "\n";
}

