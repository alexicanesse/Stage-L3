//
//  Subsample_and_aggregate.cpp
//  Stage L3
//
//  Created by Alexi Canesse on 07/06/2022.
//
#include <vector>

#include "Subsample_and_aggregate.hpp"
#include <algorithm>
#include <random>
#include <iostream>
#include <vector>


Subsample_and_aggregate::Subsample_and_aggregate(std::vector<float> (*to_compute)(std::vector<float>), std::vector<float> (*Aggregate)(std::vector<std::vector<float>>, float delta_agg, float epsilon), std::vector<float> db, int number_of_partition, float epsilon, float delta, float delta_agg){
    this->to_compute = to_compute;
    this->Aggregate = Aggregate;
    this->db = db;
    this->number_of_partition = number_of_partition;
    this->epsilon = epsilon;
    this->delta = delta;
    this->delta_agg = delta_agg;
}

std::vector<float> Subsample_and_aggregate::get_result(){
    std::vector<std::vector<float>> samples = this->randomly_partition();
    
    std::vector<std::vector<float>> computed;
    for(auto sample : samples)
        computed.push_back(this->to_compute(sample));
    
    return this->Aggregate(computed, this->delta_agg, this->epsilon);
}

std::vector<std::vector<float>> Subsample_and_aggregate::randomly_partition(){
    std::vector<float> db_copy = this->db;
    
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(db_copy.begin(), db_copy.end(), g);
    
    
    std::vector<std::vector<float>> result;
    int pos = 0;
    for(int i = 0; i < this->number_of_partition; ++i){
        std::vector<float> buff;
        
        int size = (int) db_copy.size() / this->number_of_partition;
        if(i < (db_copy.size() % this->number_of_partition)) /* distribute the value that does not fit */
            size += 1;
        
        
        for(int j = 0; j < size; ++j)
            buff.push_back(db_copy.at(pos++));
        
        
                           
        result.push_back(buff);
    }
        
    return result;
}


std::vector<float> deciles(std::vector<float> db){
    std::vector<float> db_copy = db;
    std::sort(db_copy.begin(), db_copy.end());
    
    std::vector<float> result;
    for(int i = 1; i < 10; ++i){
        result.push_back(db_copy.at(i * ((int) db_copy.size() / 10)));
    }
    
    return result;
}

float mean_10(std::vector<float> data){
    float sum = 0;
    for(int i = (int) data.size() / 10; i < (int) data.size() - (int) data.size() / 10; ++i)
        sum += data.at(i);
    
    
    return sum/(data.size() - 2*((int) data.size() / 10));
}


std::vector<float> Aggregate_10_mean(std::vector<std::vector<float>> samples_computed, float delta_agg, float epsilon){
    std::vector<std::vector<float>> computed_vals(samples_computed.at(0).size());
    
    std::vector<float> result;
    for(auto e : samples_computed)
        for(int i = 0; i < e.size(); ++i)
            computed_vals.at(i).push_back(e.at(i));
    
    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::exponential_distribution<float> d(1./(delta_agg/epsilon));
    std::uniform_int_distribution sign(0,1);
    
    for(auto e : computed_vals){
        float noise = (1./2)*d(gen)*pow((-1), sign(gen));
        result.push_back(mean_10(e) + noise);
    }
    return result;
}

float square_mean_error(std::vector<float> t1, std::vector<float> t2){
    float sum = 0;
    for(int i = 0; i < t1.size(); ++i)
        sum += pow((t1.at(i) - t2.at(i)), 2);
    
    return sqrt(sum);
}


void test_deciles_subsample_and_aggregate(int n, int k, float epsilon, float delta){
    /*
     * Test subsample and aggregate
     */
    std::random_device rd{};
    std::mt19937 gen{rd()};
    
    std::uniform_real_distribution d(0.,1.);
    std::vector<float> db;
    
    for(int i = 0; i < n; ++i)
        db.push_back(d(gen));
    
    
    /* composition theorem */
    if(delta != 0)
        epsilon /= 2*sqrt(2*9*log(1./delta));
    else
        epsilon /= 9;
    Subsample_and_aggregate sa(&deciles, &Aggregate_10_mean, db, k, epsilon, delta, 1./k);
    
    auto result(sa.get_result());
    auto real_results = deciles(db);
    
    std::cout << square_mean_error(result, real_results);
//    for(auto e : result)
//        std::cout << e << "\n";
}

