//#include "gtoa.hpp"
#include "iwo.hpp"

#include "benchmark.hpp"

#include <fstream>

void saveToCSV(const std::vector< std::map<std::string, statistics>> &stats,const std::vector<std::pair<int, int>>& params) {
    std::ofstream file("test.csv");

    if (!file.is_open()) {
        std::cerr << "Nie mo¿na otworzyæ pliku" << std::endl;
        return;
    }

    file << "Function name, Population, Iterations, Minimum, FitnessValue, stdev of Minumum, stdev of FitnessValue, v \n";
    
    auto it2 = params.begin();
    for (auto stat : stats)
    {
        for (auto it = stat.begin(); it != stat.end(); ++it) {
            file << it->first << ", ";
            file << std::to_string(it2->first) << ", ";
            file << std::to_string(it2->second) << ", ";
            file << "(";
            file << it->second.avg.resultVector;
            file << ")";
            file << ", " << std::to_string(it->second.avg.fitnessValue);
            file << ", " << it->second.stdev.resultVector;
            file << ", " << std::to_string(it->second.stdev.fitnessValue);
            file << ", " << std::to_string(it->second.calcV().fitnessValue);
            file << "\n";
        }
        ++it2;
    }

    file.close();  
}


returnValues iwoB(double (*benchmarkFunction)(const Eigen::VectorXd& x), int N, int Tmax)
{
    Params params = {Tmax, N, 0, 10, 2, 0.5, 0.001 };
    Eigen::VectorXd lb(2);
    Eigen::VectorXd ub(2);

    lb << -5, -5;
    ub << 5, 5;

    return iwo(params, 2, lb, ub, benchmarkFunction);
}

int main()
{
    int Tmax[6]{ 5, 10, 20, 40, 60, 80 };
    int N[5]{ 10, 20, 40,60, 80 };

    std::vector <std::pair<int, int>> param;
    std::vector<std::map<std::string, statistics>> stats;

    for (size_t i = 0; i < 5; i++)
    {
        for (size_t j = 0; j < 6; j++)
        {
            Params params = { Tmax[j], N[i], 0, 10, 2, 0.5, 0.001 };

            stats.push_back(evaluateMetaheuristic(iwoB, 10, N[i], Tmax[j]));
            param.push_back(std::make_pair(N[i], Tmax[j]));
            std::cout << N[i] << " " << Tmax[j];
        }
    }

	saveToCSV(stats, param);

    
    Eigen::VectorXd lb(2);
    Eigen::VectorXd ub(2);

    lb << -5, -5;
    ub << 5, 5;
    

    //returnValues test = iwo(params, 2, lb, ub, benchmarkFunction::Rastrigin);


   // std::cout << "fitnessValue: " << test.fitnessValue << "\n";
    //std::cout << "min: " << test.resultVector << "\n";

}
