#ifndef IALGORITHM_HPP
#define IALGORITHM_HPP

#include <functional>
#include <string>
#include <vector>

using fitnessFunction = std::function<double(const std::vector<double>&)>;
using VEC = std::vector<double>;
using MAT = std::vector<std::vector<double>>;

struct ParamInfo {
  size_t population;
  size_t dimensions;
  double upperBoundary;
  double lowerBoundary;
  size_t tMax;
  ParamInfo(size_t population, size_t dimensions, double upperBoundary,
            double lowerBoundary, size_t tMax)
      : population(population),
        dimensions(dimensions),
        upperBoundary(upperBoundary),
        lowerBoundary(lowerBoundary),
        tMax(tMax) {};
};

class IAlgorithm {
 public:
  virtual ~IAlgorithm() = default;

  virtual void SetParams(const ParamInfo& paramsInfo) = 0;

  virtual std::vector<double> GetXBest() const = 0;
  virtual void SetXBest(const std::vector<double>& xBest) = 0;

  virtual double GetFBest() const = 0;
  virtual void SetFBest(double fBest) = 0;

  virtual void Solve(fitnessFunction f) = 0;
};

#endif  // IALGORITHM_HPP