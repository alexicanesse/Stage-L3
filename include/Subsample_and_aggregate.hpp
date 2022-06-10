//
//  Subsample_and_aggregate.hpp
//  Stage L3
//
//  Created by Alexi Canesse on 07/06/2022.
//

#ifndef Subsample_and_aggregate_hpp
#define Subsample_and_aggregate_hpp

#include <stdio.h>
#include <vector>
#include <functional>

class Subsample_and_aggregate{
public:
    Subsample_and_aggregate(std::vector<double> (*to_compute)(std::vector<double>&), std::vector<double> (*Aggregate)(std::vector<std::vector<double>>, double delta_agg, double epsilon), std::vector<double> db, int number_of_partition, double epsilon, double delta, double delta_agg);
    
    std::vector<double> get_result();
private:
    int number_of_partition;
    std::vector<double> db;
    std::vector<std::vector<double>> randomly_partition();
    double epsilon;
    double delta;
    std::vector<double> (*to_compute)(std::vector<double>&);
    std::vector<double> (*Aggregate)(std::vector<std::vector<double>>, double delta_agg, double epsilon);
    double delta_agg;
};

std::vector<double> Aggregate_10_mean(std::vector<std::vector<double>> samples_computed);
void test_deciles_subsample_and_aggregate(int n, int k, double epsilon, double delta);

#endif /* Subsample_and_aggregate_hpp */
