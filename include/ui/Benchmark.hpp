#ifndef BENCHMARK_HPP
#define BENCHMARK_HPP

#include <cmath>
#include <iostream>
#include <vector>

#include "../algorithms/AlgorithmFactory.hpp"
#include "AlgorithmData.hpp"

using fitnessFunction = std::function<double(const std::vector<double> &)>;
using data = std::vector<std::shared_ptr<AlgorithmData>>;

struct Result {
  std::string name;
  std::string functionName;
  ParamInfo params;
  VEC XBest;
  double FBest;
};

class Benchmark {
 public:
  Benchmark();

  void Run(const data &algorithms);

 private:
  std::vector<Result> results;
  std::unordered_map<std::string, fitnessFunction> functions;
};

#endif  // BENCHMARK_HPP