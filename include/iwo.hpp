#ifndef IWO_HPP
#define IWO_HPP

#include "returnValues.hpp"

using VEC = Eigen::VectorXd;
using MAT = Eigen::MatrixXd;

struct Params {
	int tMax;
	int populationSize;
	int minSeeds;
	int maxSeeds;
	int n;
	double initSigma;
	double finalSigma;
};

namespace IWO{
    returnValues algorithm(Params params, int dimensions, VEC lowerBounds, VEC upperBounds, double (*fitnessFunction)(const VEC&));
    MAT generatePopulation(VEC L, VEC U, int N, int D);
    MAT sortByFitness(const MAT& m, double (*fitnessFunction)(const VEC&));
}

#endif // IWO_HPP
