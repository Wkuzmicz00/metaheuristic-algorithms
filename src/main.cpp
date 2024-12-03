#include "../include/gtoa.hpp"
#include "../include/iwo.hpp"
#include "../include/benchmark.hpp"

#include <fstream>
#include <format>

std::string vecToString(Eigen::VectorXd vec){
    std::string result = "(";
    for(size_t i=0; i < vec.cols(); ++i){
        result += std::to_string(vec(i)) + ". ";
    }
    result += std::to_string(vec(vec.cols())) + ")";
    return result;
}

void saveToCSV(std::string fileName, const std::vector< std::map<std::string, statistics>> &stats,const std::vector<std::pair<int, int>>& params) {
    std::ofstream file(fileName);

    if (!file.is_open()) {
        std::cerr << "Nie mozna otworzyc pliku" << std::endl;
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
            file << vecToString(it->second.avg.resultVector);
            file << ", " << std::to_string(it->second.avg.fitnessValue);
            file << ", " << vecToString(it->second.stdev.resultVector);
            file << ", " << std::to_string(it->second.stdev.fitnessValue);
            file << ", " << std::to_string(it->second.calcV().fitnessValue);
            file << "\n";
        }
        ++it2;
    }

    file.close();
}


returnValues iwo(double (*benchmarkFunction)(const Eigen::VectorXd& x), int N, int Tmax)
{
    Params params = {Tmax, N, 0, 10, 2, 0.5, 0.001 };
    //
    Eigen::VectorXd lb(2);
    Eigen::VectorXd ub(2);

    lb << -5, -5;
    ub << 5, 5;

    return IWO::algorithm(params, 2, lb, ub, benchmarkFunction);
}

returnValues gtoa(double (*benchmarkFunction)(const Eigen::VectorXd& x), int N, int Tmax)
{
    return GTOA::algorithm(Tmax, N, -5, 5, 2, benchmarkFunction);
}

int main()
{
    int Tmax[6]{ 5, 10, 20, 40, 60, 80 };
    int N[5]{ 10, 20, 40,60, 80 };

    std::vector <std::pair<int, int>> param;
    std::vector<std::map<std::string, statistics>> stats;

    for (size_t i = 0; i < 5; i++){
        for (size_t j = 0; j < 6; j++){
            stats.push_back(evaluateMetaheuristic(iwo, 10, N[i], Tmax[j]));
            param.push_back(std::make_pair(N[i], Tmax[j]));
        }
    }

	saveToCSV("iwo-stats.csv", stats, param);

	param.clear();
	stats.clear();
	for (size_t i = 0; i < 5; i++){
        for (size_t j = 0; j < 6; j++){
            stats.push_back(evaluateMetaheuristic(gtoa, 10, N[i], Tmax[j]));
            param.push_back(std::make_pair(N[i], Tmax[j]));
        }
    }

    saveToCSV("gtoa-stats.csv", stats, param);
}
