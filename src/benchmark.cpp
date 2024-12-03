#include "benchmark.hpp"


statistics::statistics(returnValues avg, returnValues stdev) : avg(avg), stdev(stdev) {};
returnValues statistics::calcV() const{
	return (stdev * 100 / avg);
}

double benchmarkFunction::Rosenbrock(const Eigen::VectorXd& x){
	if (x.size() < 2) {
		throw std::invalid_argument("Input vector must have at least 2 dimensions for the Rosenbrock function.");
	}

	double result = 0.0;
	for (int i = 0; i < x.size() - 1; ++i) {
		double xi = x[i];
		double xi_next = x[i + 1];
		result += 100 * std::pow(xi_next - xi * xi, 2) + std::pow(1 - xi, 2);
	}

	return result;
}

double benchmarkFunction::Sphere(const Eigen::VectorXd& x) {
	return x.squaredNorm();
}

double benchmarkFunction::Rastrigin(const Eigen::VectorXd& x) {
	double A = 10.0;
	double n = x.size();
	double result = A * n;
	for (int i = 0; i < x.size(); ++i) {
		result += x[i] * x[i] - A * std::cos(2 * PI * x[i]);
	}
	return result;
}

double benchmarkFunction::Himmelbau(const Eigen::VectorXd& x) {
	double x1 = x(0);
	double x2 = x(1);
	return std::pow(std::pow(x1, 2) + x2 - 11, 2) + std::pow(x1 + std::pow(x2, 2) - 7, 2);
}

double benchmarkFunction::Bukin(const Eigen::VectorXd& x) {
	double x1 = x(0);
	double x2 = x(1);
	return 100.0 * std::sqrt(std::abs(x2 - 0.01 * std::pow(x1, 2))) + 0.01 * std::abs(x1 + 10.0);
}

double benchmarkFunction::Beale(const Eigen::VectorXd& x) {
	double x1 = x(0);
	double x2 = x(1);
	return std::pow(1.5 - x1 + x1 * x2, 2) +
		std::pow(2.25 - x1 + x1 * std::pow(x2, 2), 2) +
		std::pow(2.625 - x1 + x1 * std::pow(x2, 3), 2);
}

std::map<std::string,statistics> evaluateMetaheuristic
	(returnValues (*Metaheuristic)(double(*benchmarkFunction)(const Eigen::VectorXd& x), int N, int Tmax), int iter, int N, int Tmax) {

	std::map<std::string, double (*)(const Eigen::VectorXd&)> benchmarkFunctions = {
		{"Rastrigin", benchmarkFunction::Rastrigin},
		{"Rosenbrock", benchmarkFunction::Rosenbrock},
		{"Sphere", benchmarkFunction::Sphere},
		{"Bukin", benchmarkFunction::Bukin},
		{"Beale", benchmarkFunction::Beale},
		{"Himmelbau", benchmarkFunction::Himmelbau},
	};

	std::map<std::string, statistics> results;

	std::vector<returnValues> data;

	for (auto it = benchmarkFunctions.begin(); it != benchmarkFunctions.end(); ++it){
		data.clear();
		for (size_t i = 0; i < iter; ++i) {
			data.push_back(Metaheuristic(it->second, N, Tmax));
		}
		statistics stat = calculate(data, data[0].resultVector.size());
		results[it->first] = stat;
	}


	return results;
}

statistics calculate(const std::vector<returnValues>& data, size_t len) {
	
	returnValues avg(0.0, Eigen::RowVectorXd::Zero(len));
	returnValues stdev(0.0, Eigen::RowVectorXd::Zero(len));

	for (returnValues rv : data)
		avg = avg + rv;

	avg = avg / data.size();

	for (returnValues rv : data)
		stdev = stdev + (rv - avg).pow(2);

	stdev = stdev / data.size();

	return statistics(avg, stdev);
}