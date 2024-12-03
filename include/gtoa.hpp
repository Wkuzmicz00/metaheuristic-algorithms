#ifndef GTOA_HPP
#define GTOA_HPP

#include "../include/returnValues.hpp"

using VEC = Eigen::VectorXd;
using MAT = Eigen::MatrixXd;

namespace GTOA {
    Eigen::MatrixXd initializationMatrix(int l, int u, int N, int D);
    Eigen::MatrixXd sortByFitness(const Eigen::MatrixXd& m, double (*fitnessFunction)(const Eigen::VectorXd&));
    returnValues algorithm(int Tmax, int Population, int lowerBounds, int upperBounds, int Dimensions, double (*fitnessFunction)(const Eigen::VectorXd&));
}


#endif // GTOA_HPP
