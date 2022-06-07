//
//  Inverse_sensitivity.cpp
//  Stage L3
//
//  Created by Alexi Canesse on 07/06/2022.
//

#include "Inverse_sensitivity.hpp"

#include <vector>
#include <algorithm>
#include <cmath>

int len_quantile(std::vector<float> x, float coef_quantile, float goal){
    /* do not pay the sorting part if the db is already sorted */
    if(!std::is_sorted(x.begin(), x.end()))
        std::sort(x.begin(), x.end());
    
    
    auto quantile_it = x.begin() + std::ceil(x.size()*coef_quantile) - 1; /* iterator to the quantile position */
    auto it = quantile_it;
    if(*quantile_it == goal)
        return 0;
    else if(*quantile_it > goal)
        it = upper_bound(x.begin(), x.end(), goal); /* iterator to the first element that is greater than goal, or last if no such element is found. */
    else{
        it = lower_bound(x.begin(), x.end(), goal); /* iterator to the first element that is not less than value, or last if no such element is found. */
        it--;
    }
    
    return (int) std::abs(quantile_it - it) + 1;
}
