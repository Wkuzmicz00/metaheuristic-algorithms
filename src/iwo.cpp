#include "../include/iwo.hpp"

#include <cmath>

returnValues IWO::algorithm(Params params, int dimensions, VEC lowerBounds, VEC upperBounds, double (*fitnessFunction)(const VEC&)){

	std::random_device rd;
	std::mt19937 gen(rd());
	std::normal_distribution<> normDis(0.0, 1.0);

	int t = 0;

	//Initial population
	MAT population = generatePopulation(lowerBounds, upperBounds, params.populationSize, dimensions);
	population = sortByFitness(population, fitnessFunction);

	while (t < params.tMax)
	{

		int currentPopulationSize = population.rows();

		//Reproduction
		double bestF = fitnessFunction(population.row(0));
		double worstF = fitnessFunction(population.row(currentPopulationSize - 1));

		VEC Sp = VEC::Zero(currentPopulationSize);

		if (bestF - worstF == 0)
			return returnValues(fitnessFunction(population.row(0)), population.row(0));

		for (size_t i = 0; i < currentPopulationSize; i++) {
			double fitness = fitnessFunction(population.row(i));
			Sp(i) = std::ceil(params.minSeeds + (fitness - worstF) * ((params.maxSeeds - params.minSeeds) / (bestF - worstF)));
		}

		//Spatial distibution
		double stdev = (std::pow(params.tMax - t, params.n) / std::pow(params.tMax, params.n)) * (params.initSigma - params.finalSigma) + params.finalSigma;

		int sum = Sp.sum();

		MAT newPopulation = MAT::Zero(sum, dimensions);
		size_t iter = 0;

		for (size_t pop = 0; pop < currentPopulationSize; ++pop) {
			for (size_t seedpop = 0; seedpop < Sp(pop); ++seedpop) {
				for (size_t dim = 0; dim < dimensions; ++dim) {
					newPopulation(iter, dim) = population(pop, dim) + stdev * normDis(gen);
				}
				iter += 1;
			}
		}

		//Competetive Elimination
		newPopulation.conservativeResize(population.rows() + newPopulation.rows(), dimensions);
		newPopulation.bottomRows(population.rows()) = population;

		newPopulation = sortByFitness(newPopulation, fitnessFunction);
		population = newPopulation.block(0, 0, params.populationSize, dimensions);

		t++;
	}

	return returnValues(fitnessFunction(population.row(0)), population.row(0));
}

MAT IWO::generatePopulation(VEC L, VEC U, int N, int D) {
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_real_distribution<> dis(0.0, 1.0);
	//Jakie wartosci random?

	Eigen::MatrixXd population(N, D);
	for (size_t i = 0; i < D; i++)
		for (size_t j = 0; j < N; j++)
			population(j, i) = L(i) + dis(gen) * (U(i) - L(i));


	return population;
}

MAT IWO::sortByFitness(const MAT& m, double (*fitnessFunction)(const VEC&))
{
	std::vector<std::pair<int, double>> fitnessValues;
	fitnessValues.reserve(m.rows());

	for (size_t i = 0; i < m.rows(); i++)
		fitnessValues.push_back({ i, fitnessFunction(m.row(i)) });

	std::sort(fitnessValues.begin(), fitnessValues.end(),
		[](const std::pair<int, double>& a, const std::pair<int, double>& b) {return a.second < b.second; });


	MAT sortedMatrix(m.rows(), m.cols());

	for (size_t j = 0; j < m.rows(); j++)
		sortedMatrix.row(j) = m.row(fitnessValues[j].first);

	return sortedMatrix;
}
