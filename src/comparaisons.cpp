//
//  comparaisons.cpp
//  Stage L3
//
//  Created by Alexi Canesse on 20/06/2022.
//

#include "comparaisons.hpp"
#include "inverse_sensitivity.hpp"
#include "myrtille.hpp"
#include "random.hpp"
#include "common_tools.hpp"

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>

extern class random rdm;

void myrtille_against_inverse_sensitivity_graph_uniforme(int max_n, double epsilon){
    std::stringstream ss;
    
    for(int n = 1; n < max_n; n+=20){
        std::vector<double> db = rdm.generate_db(n, [](){ return rdm.Uniforme(0, 1); });
        std::vector<double> resultMyrtille = myrtille(db, epsilon, 0, 1, 1000);
        std::vector<double> resultInverseSensitivity = inverset_sensitivity(db, epsilon, 0, 1, 0.001);
        std::vector<double >real_results = deciles(db);

        ss << "\\filldraw[magenta] (" << n << ", " << square_mean_error(resultMyrtille, real_results) << ") circle (1pt) ;\n";
        ss << "\\filldraw[blue] (" << n << ", " << square_mean_error(resultInverseSensitivity, real_results) << ") circle (1pt) ;\n";
    }
    
    std::ofstream outFile("./proofs/source/myrtille_against_inverse_sensitivity_graph_uniforme.tex");
    outFile << ss.rdbuf();
    outFile.close();
}
