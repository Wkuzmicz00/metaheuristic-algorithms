#ifndef RETURN_VALUES_HPP
#define RETURN_VALUES_HPP

#include <iostream>
#include <random>

#include <C:\Users\wojte\source\repos/inz_ai/Eigen/Dense>


struct returnValues {
	double fitnessValue;
	Eigen::VectorXd resultVector;

	returnValues(double fitnessValue, Eigen::VectorXd resultVector) :
		fitnessValue(fitnessValue), resultVector(std::move(resultVector)) {};

	returnValues(){};

	returnValues operator+(const returnValues& a) const {
		return returnValues(this->fitnessValue + a.fitnessValue, this->resultVector + a.resultVector);
	}

	returnValues operator/(double scalar) const {
		return returnValues(this->fitnessValue / scalar, this->resultVector / scalar);
	}
	returnValues operator*(double scalar) const {
		return returnValues(this->fitnessValue * scalar, this->resultVector * scalar);
	}

	returnValues operator/(const returnValues& a) const {
		return returnValues(this->fitnessValue / a.fitnessValue, this->resultVector.array() / a.resultVector.array());
	}

	returnValues operator-(const returnValues& a) const {
		return returnValues(this->fitnessValue - a.fitnessValue, this->resultVector - a.resultVector);
	}

	returnValues pow(int n) {
		return returnValues(std::pow(this->fitnessValue, n), this->resultVector.array().pow(n));
	}

	returnValues sqrt() {
		return returnValues(std::sqrt(this->fitnessValue), this->resultVector.array().sqrt());
	}
};

#endif // RETURN_VALUES_HPP