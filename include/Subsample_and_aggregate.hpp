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

class Subsample_and_aggregate{
public:
    Subsample_and_aggregate(std::vector<float> (*to_compute)(std::vector<float>), std::vector<float> (*Aggregate)(std::vector<std::vector<float>>, float delta_agg, float epsilon), std::vector<float> db, int number_of_partition, float epsilon, float delta, float delta_agg);
    
    std::vector<float> get_result();
private:
    int number_of_partition;
    std::vector<float> db;
    std::vector<std::vector<float>> randomly_partition();
    float epsilon;
    float delta;
    std::vector<float> (*to_compute)(std::vector<float>);
    std::vector<float> (*Aggregate)(std::vector<std::vector<float>>, float delta_agg, float epsilon);
    float delta_agg;
};

std::vector<float> deciles(std::vector<float> db);
float mean_10(std::vector<float> data);
std::vector<float> Aggregate_10_mean(std::vector<std::vector<float>> samples_computed);
void test_deciles_subsample_and_aggregate(int n, int k, float epsilon, float delta);
float square_mean_error(std::vector<float> t1, std::vector<float> t2);

#endif /* Subsample_and_aggregate_hpp */
