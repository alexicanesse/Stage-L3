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
#include <boost/math/special_functions/beta.hpp>


extern class random rdm;

void myrtille_against_inverse_sensitivity_graph_uniforme(int max_n, double epsilon){
    std::stringstream ss;
    
    for(int n = 1; n < max_n; n+=20){
        std::vector<double> db = rdm.generate_db(n, [](){ return rdm.Uniforme(0, 1); });
        std::vector<double> resultMyrtille = myrtille(db, epsilon, 0, 1);
        std::vector<double> resultInverseSensitivity = inverset_sensitivity(db, epsilon);
        std::vector<double >real_results = deciles(db);

        ss << "\\filldraw[magenta] (" << n << ", " << square_mean_error(resultMyrtille, real_results) << ") circle (1pt) ;\n";
        ss << "\\filldraw[blue] (" << n << ", " << square_mean_error(resultInverseSensitivity, real_results) << ") circle (1pt) ;\n";
    }
    
    std::ofstream outFile("./proofs/source/myrtille_against_inverse_sensitivity_graph_uniforme.tex");
    outFile << ss.rdbuf();
    outFile.close();
}


void real_data_graph(){
//    ss << "\\documentclass[crop,tikz]{standalone}\n\\usepackage{pgfplots}\n\\pgfplotsset{compat=1.18}\n \\begin{document}\n\\begin{tikzpicture}\n\\begin{axis}[width=0.7\\textwidth,height=0.7\\textwidth,samples=600,axis x line=middle,axis y line=middle,ymin = 0, ymax = 1000, xmin = 0, xmax = 1]\n";
    
    std::ifstream inFile("./raw_data/salaries.csv");
    std::string str = "";
    
    std::vector<double> salaries;
    
    while(getline(inFile, str)){
        for(int i = 0; i < 12; ++i)
            getline(inFile, str, ';');
        
        if(!str.empty()){
            while(str.find(',') != std::string::npos)
                str.erase(str.find(','), 1);
            salaries.push_back(std::stod(str));
        }
    }
//    for(int k = 0; k < 20; ++k){
    
    double sqr;
    double sqr_is;
    while(1){
        double epsilon = rdm.Uniforme(0.1, 1);
        std::cout << epsilon << "\n";
        auto result_is = inverset_sensitivity(salaries, epsilon);
        auto result = myrtille(salaries, epsilon, 0, *std::max_element(salaries.begin(), salaries.end()));
        auto real_result = deciles(salaries);
        
        
        sqr_is = square_mean_error(real_result, result_is);
        sqr = square_mean_error(real_result, result);
        std::stringstream ss;
        ss << "\\filldraw[magenta] (" << epsilon << ", " << sqr << ") circle (0.5pt) ;\n";
        ss << "\\filldraw[blue] (" << epsilon << ", " << sqr_is << ") circle (0.5pt) ;\n";
        std::ofstream outFile;
        outFile.open("./raw_data/fig2.tex", std::ios_base::app);
        outFile << ss.rdbuf();
        outFile.close();
        smooting("./raw_data/fig2");
    }
//
//    }
}

bool comp_x(std::vector<double> a, std::vector<double> b){
    return a.at(0) < b.at(0);
}

void smooting(std::string file){
    std::ifstream inFile(file + ".tex");
    std::string str = "";
    
    std::vector<std::vector<double>> points;
    std::vector<std::vector<double>> points_is;
    int i = 0;
    while(1){
        if(i % 2 == 0){//histo
            getline(inFile, str, '(');
            getline(inFile, str, ',');
            if(str.empty())
                break;
            double x = stod(str);
            getline(inFile, str, ')');
            str.erase(str.find(' '), 1);
            double y = stod(str);
            points.push_back(std::vector<double>{x, y});
        }
        else{//is
            getline(inFile, str, '(');
            getline(inFile, str, ',');
            if(str.empty())
                break;
            double x = stod(str);
            getline(inFile, str, ')');
            str.erase(str.find(' '), 1);
            double y = stod(str);
            points_is.push_back(std::vector<double>{x, y});
        }
        ++i;
        getline(inFile, str, '\n');
    }
    std::sort(points.begin(), points.end(), comp_x);
    std::sort(points_is.begin(), points_is.end(), comp_x);

    std::stringstream ss;
    std::stringstream ss_is;
    int n = (int) points.size();

    for(int i = 100; i < n - 100; i++){
        double sum = 0;
        double sum_is = 0;
        for(int j = -100; j < 100; ++j){
            sum += points.at(i + j).at(1);
            sum_is += points_is.at(i + j).at(1);
        }
        sum /= 200;
        sum_is /= 200;
            
        ss << points.at(i).at(0) << " " << sum << "\n";
        ss_is << points_is.at(i).at(0) << " " << sum_is << "\n";
        
        
    }
    std::ofstream outFile;
    outFile.open(file + "_lines.dot");
    std::ofstream outFile_is;
    outFile_is.open(file + "_lines_is.dot");
    outFile << ss.rdbuf();
    outFile.close();
    outFile_is << ss_is.rdbuf();
    outFile_is.close();
}



void uniform_graph(){
    int number_exec = 25;
    double epsilon = 0.5;
    
    
    std::vector<double> data;
    
    for(int n = 3553; n < 5000; n += 4){
        double rslt = 0;
        double rslt_is = 0;
        for(int i = 0; i < number_exec; ++i){
            std::cout << n << " : " << i << "\n";
            
            std::vector<double> data = rdm.generate_db(n, [](){ return rdm.Uniforme(0, 1); });
            auto result_is = inverset_sensitivity(data, epsilon);
            auto result = myrtille(data, epsilon, 0, 1);
            auto real_result = deciles(data);
            
            rslt += square_mean_error(result, real_result)/number_exec;
            rslt_is += square_mean_error(result_is, real_result)/number_exec;
        }
        
        std::stringstream ss;
        ss << "\\filldraw[magenta, opacity=0.5] (" << n << ", " << rslt << ") circle (0.2pt) ;\n";
        ss << "\\filldraw[blue, opacity=0.5] (" << n << ", " << rslt_is << ") circle (0.2pt) ;\n";
        std::ofstream outFile;
        outFile.open("./raw_data/fig3_" + std::to_string(epsilon) + ".tex", std::ios_base::app);
        outFile << ss.rdbuf();
        outFile.close();
    }
}


void light_version(std::string file){
    std::ifstream inFile(file + ".tex");
    std::string str = "";
    
    std::stringstream ss;
    int i = 0;
    while(getline(inFile, str, '\n')){
        if(i++ % 2){
            ss << str << "\n";
            getline(inFile, str, '\n');
            ss << str << "\n";
        }
        else
            getline(inFile, str, '\n');
    }
     
    std::ofstream outFile;
    outFile.open(file + "_light.tex");
    outFile << ss.rdbuf();
    outFile.close();
}

void normale_graph(){
    int number_exec = 20;
    double epsilon = 0.5;
    
    
    std::vector<double> data;
    
    for(int n = 8140; n < 10000; n += 5){
        double rslt = 0;
        double rslt_is = 0;
        for(int i = 0; i < number_exec; ++i){
            std::cout << n << " : " << i << "\n";
            
            std::vector<double> data = rdm.generate_db(n, [](){ return rdm.Normale(0, 1); });
            auto result_is = inverset_sensitivity(data, epsilon);
            auto result = myrtille(data, epsilon, *std::min_element(data.begin(), data.end()), *std::max_element(data.begin(), data.end()));
            auto real_result = deciles(data);
            
            
            rslt += square_mean_error(result, real_result)/number_exec;
            rslt_is += square_mean_error(result_is, real_result)/number_exec;
        }
        
        std::stringstream ss;
        ss << "\\filldraw[magenta, opacity=0.5] (" << n << ", " << rslt << ") circle (0.2pt) ;\n";
        ss << "\\filldraw[blue, opacity=0.5] (" << n << ", " << rslt_is << ") circle (0.2pt) ;\n";
        std::ofstream outFile;
        outFile.open("./raw_data/fig4_" + std::to_string(epsilon) + ".tex", std::ios_base::app);
        outFile << ss.rdbuf();
        outFile.close();
    }
}


void output_graphe_borne_esperance(){
    std::stringstream ss;
    double eps = 0.25;
    int i = 1;
    for(int n = 4380; n < 8000; n+=10){
        std::cout << n << "\n";
        double alpha = 8*log(3*n*sqrt(n))/eps;
        double val = 2*log(n)/(3*n)
        + i*0.1/(sqrt(n)*log(n))
        + numericIntegration((std::function<double(double)>) [alpha, n, i](double t){ return 1 - boost::math::ibeta(i*n/10 + alpha, n - i*n/10 - alpha + 1, 0.1*i + t); }, 0, 0.1, 0.00001)
        + numericIntegration((std::function<double(double)>) [alpha, n, i](double t){ return boost::math::ibeta(i*n/10 - alpha, n - i*n/10 + alpha + 1, i*0.1 - t); }, 0, 0.1, 0.00001)
        + (1/(sqrt(n)*log(n)) + boost::math::ibeta(i*n/10 - alpha, n - i*n/10 + alpha + 1, 0.1*i - 0.1) + boost::math::ibeta(n - i*n/10 - alpha + 1, i*n/10 + alpha, 1 - 0.1 - 0.1*i));
        
//        if(val < 0.5)
        ss << n << " " << val << "\n";
    }
    
    std::ofstream outFile;
    outFile.open("./raw_data/fig5_" + std::to_string(eps) + ".dot", std::ios_base::app);
    outFile << ss.rdbuf();
    outFile.close();
}


void borne_decile_uniforme(){
    std::stringstream ss;
    
    for(int n = 10; n < 10000; ++n){
        std::vector<double> errs;
        for(int k = 0; k < 21; ++k){
            std::vector<double> x = rdm.generate_db(n, [](){ return rdm.Uniforme(0, 1); });
            double d0 = myrtille(x, 1, 0, 1).at(0);
            errs.push_back(std::abs(d0 - 0.1));
        }
        
        sort(errs.begin(), errs.end());
        ss << n << " " << errs.at(10) << "\n";
    }
    std::ofstream outFile;
    outFile.open("./raw_data/fig6.dot", std::ios_base::app);
    outFile << ss.rdbuf();
    outFile.close();
}


void deciles_uniforme_func_eps(){
    int number_exec = 100;
    std::vector<double> data;
    
    for(double epsilon = 0.05; epsilon < 0.06; epsilon += 0.1){
        double rslt = 0;
        double rslt_is = 0;
        
        for(int i = 0; i < number_exec; ++i){
            std::cout << epsilon << " : " << i << "\n";
            
            std::vector<double> data = rdm.generate_db(10000, [](){ return rdm.Uniforme(0, 1); });
            auto result_is = inverset_sensitivity(data, epsilon);
            auto result = myrtille(data, epsilon, 0, 1);
            auto real_result = std::vector<double>{0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};
            
            rslt += square_mean_error(result, real_result);
            rslt_is += square_mean_error(result_is, real_result);
        }
        
        std::stringstream ss;
        std::stringstream ss_is;
        ss << std::to_string(epsilon) << " " << std::to_string(rslt/number_exec) << "\n";
        ss_is << std::to_string(epsilon) << " " << std::to_string(rslt_is/number_exec) << "\n";
        
        std::ofstream outFile;
        outFile.open("./raw_data/QyyxyXwhYDSyIhBt.dot", std::ios_base::app);
        outFile << ss.rdbuf();
        outFile.close();
        
        std::ofstream outFile_is;
        outFile_is.open("./raw_data/QyyxyXwhYDSyIhBt_is.dot", std::ios_base::app);
        outFile_is << ss_is.rdbuf();
        outFile_is.close();
    }
}
