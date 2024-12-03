#ifndef BENCHMARK_HPP
#define BENCHMARK_HPP

#include <string>
#include <map>

#include "returnValues.hpp"

constexpr double PI = 3.14159265358979323846;

struct statistics {
	returnValues avg;
	returnValues stdev;

	statistics(returnValues avg, returnValues stdev);
	statistics() {};

	returnValues calcV() const;
};

namespace benchmarkFunction
{
	double Rosenbrock(const Eigen::VectorXd& x);
	double Rastrigin(const Eigen::VectorXd& x);
	double Sphere(const Eigen::VectorXd& x);
}

std::map<std::string, statistics> evaluateMetaheuristic(returnValues(*Metaheuristic)(double(*benchmarkFunction)(const Eigen::VectorXd& x), int N, int Tmax), int n, int D, int Tmax);
statistics calculate(const std::vector<returnValues>& data, size_t len);

#endif // BENCHMARK_HPP
