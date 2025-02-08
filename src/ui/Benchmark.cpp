#include "../include/ui/Benchmark.hpp"

#include <QDebug>
namespace Functions {
double sphere(const std::vector<double>& x) {
  double sum = 0.0;
  for (double xi : x) {
    sum += xi * xi;
  }
  return sum;
}

double rastrigin(const std::vector<double>& x) {
  const double A = 10.0;
  double sum = A * static_cast<double>(x.size());
  for (double xi : x) {
    sum += xi * xi - A * cos(2.0 * M_PI * xi);
  }
  return sum;
}

double rosenbrock(const std::vector<double>& x) {
  if (x.size() < 2) {
    return std::numeric_limits<double>::max();
  }
  double sum = 0.0;
  for (size_t i = 0; i < x.size() - 1; i++) {
    double xi = x[i];
    double xi1 = x[i + 1];
    sum += 100.0 * pow(xi1 - xi * xi, 2) + pow(xi - 1.0, 2);
  }
  return sum;
}
}  // namespace Functions

Benchmark::Benchmark() {
  functions["rastrigin"] = Functions::rastrigin;
  // functions["sphere"] = Functions::sphere;
  // functions["rosenbrock"] = Functions::rosenbrock;
}

void Benchmark::Run(const data& algorithms) {
  for (std::shared_ptr<AlgorithmData> algorithmData : algorithms) {
    qDebug() << algorithms.size();
    std::vector<ParamInfo> params = algorithmData->getParams();

    for (ParamInfo param : params) {
      IAlgorithm* algorithm =
          AlgorithmFactory::Instance().Create(algorithmData->getName());

      qDebug() << param.dimensions << param.population << param.upperBoundary
               << param.lowerBoundary << param.tMax;

      // algorithm->SetParams(param);
      for (const auto& pair : functions) {
        algorithm->Solve(pair.second);
        Result result = Result(algorithmData->getName(), pair.first, param,
                               algorithm->GetXBest(), algorithm->GetFBest());
        results.push_back(result);
      }
    }
  }

  // for (auto result : results)
  qDebug() << results[0].FBest;
}