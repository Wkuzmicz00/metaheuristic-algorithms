#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>

#include "IAlgorithm.hpp"

class InverseWeedOptimizer : public IAlgorithm {
 private:
  ParamInfo parameters;

  // RETURN
  std::vector<double> XBest;
  double FBest;

 public:
  InverseWeedOptimizer()
      : parameters(ParamInfo(1, 1.0, 1.0, 1, 1)), FBest(0.0) {}

  void SetParams(const ParamInfo &params) override { parameters = params; }

  std::vector<double> GetXBest() const override { return XBest; }
  void SetXBest(const std::vector<double> &newXBest) override {
    XBest = newXBest;
  }

  double GetFBest() const override { return FBest; }
  void SetFBest(double newFBest) override { this->FBest = newFBest; }

 public:
  void Solve(fitnessFunction f) override {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> normDis(0.0, 1.0);

    size_t t = 0;

    // Initial population
    MAT population =
        generatePopulation(parameters.lowerBoundary, parameters.upperBoundary,
                           parameters.population, parameters.dimensions);

    population = sortByFitness(population, f);

    while (t < parameters.tMax) {
      // Reproduction
      double bestF = f(population[0]);
      double worstF =
          f(population[static_cast<size_t>(parameters.population) - 1]);

      std::vector<size_t> Sp = std::vector<size_t>(parameters.population, 0);

      if (bestF - worstF == 0) break;

      for (size_t i = 0; i < static_cast<size_t>(parameters.population); i++) {
        double fitness = f(population[i]);
        Sp[i] = static_cast<size_t>(
            std::ceil(0 + (fitness - worstF) * ((5 - 0) / (bestF - worstF))));
      }

      // Spatial distibution
      double stdev =
          (std::pow(parameters.tMax - t, 2) / std::pow(parameters.tMax, 2)) *
              (0.5 - 0.01) +
          0.01;

      size_t sum =
          static_cast<size_t>(std::accumulate(Sp.begin(), Sp.end(), 0));

      MAT newPopulation = MAT(sum, VEC(parameters.dimensions, 0));
      size_t iter = 0;

      for (size_t pop = 0; pop < parameters.population; ++pop) {
        for (size_t seedpop = 0; seedpop < Sp[pop]; ++seedpop) {
          for (size_t dim = 0; dim < parameters.dimensions; ++dim) {
            newPopulation[iter][dim] =
                population[pop][dim] + stdev * normDis(gen);
          }
          iter += 1;
        }
      }

      // Competetive Elimination
      newPopulation.insert(newPopulation.end(), population.begin(),
                           population.end());

      newPopulation = sortByFitness(newPopulation, f);
      newPopulation.erase(
          newPopulation.begin() + static_cast<long>(parameters.population),
          newPopulation.end());
      population = newPopulation;

      t++;
    }

    SetXBest(population[0]);
    SetFBest(f(population[0]));
  }

  MAT generatePopulation(double L, double U, size_t N, size_t D) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<> dis(0.0, 1.0);

    MAT population(N, std::vector<double>(D, 0));

    for (size_t i = 0; i < D; i++) {
      for (size_t j = 0; j < N; j++) {
        population[j][i] = L + dis(gen) * (U - L);
      }
    }
    return population;
  }

  MAT sortByFitness(const MAT &m, fitnessFunction f) {
    std::vector<std::pair<size_t, double>> fitnessValues;
    fitnessValues.reserve(m.size());

    for (size_t i = 0; i < m.size(); i++) fitnessValues.push_back({i, f(m[i])});

    std::sort(
        fitnessValues.begin(), fitnessValues.end(),
        [](const std::pair<int, double> &a, const std::pair<int, double> &b) {
          return a.second < b.second;
        });

    MAT sortedMatrix(m.size(), VEC(m[0].size(), 0));

    for (size_t j = 0; j < m[0].size(); j++)
      sortedMatrix[j] = m[fitnessValues[j].first];

    return sortedMatrix;
  }
};

extern "C" IAlgorithm *Create() { return new InverseWeedOptimizer(); }
