//#include "gtoa.hpp"
//
//
//Eigen::MatrixXd initializationMatrix(int l, int u, int N, int D) {
//	std::random_device rd;
//	std::mt19937 gen(rd());
//
//	std::normal_distribution<> dis(0.0, 1.0);
//
//	double random_number = 0;
//
//	Eigen::MatrixXd matrix(N, D);
//	for (size_t i = 0; i < N; i++) {
//		for (size_t j = 0; j < D; j++) {
//			random_number = dis(gen);
//			matrix(i, j) = l + (u - l) * random_number;
//		}
//	}
//	return matrix;
//}
//
//Eigen::MatrixXd sortByFitnes(const Eigen::MatrixXd& m, double (*fitnessFunction)(const Eigen::RowVectorXd&))
//{
//	std::vector<std::pair<int, double>> fitnessValues;
//	fitnessValues.reserve(m.rows());
//
//	for (size_t i = 0; i < m.rows(); i++)
//		fitnessValues.push_back({ i, fitnessFunction(m.row(i)) });
//
//	std::sort(fitnessValues.begin(), fitnessValues.end(),
//		[](const std::pair<int, double>& a, const std::pair<int, double>& b) {return a.second < b.second;});
//
//
//	Eigen::MatrixXd sortedMatrix(m.rows(), m.cols());
//
//	for (size_t j = 0; j < m.rows(); j++)
//		sortedMatrix.row(j) = m.row(fitnessValues[j].first);
//
//	return sortedMatrix;
//}
//
//returnValues GTOA(int Tmax, int Population, int lowerBounds, int upperBounds, int Dimensions, double (*fitnessFunction)(const Eigen::RowVectorXd&))
//{
//	Eigen::MatrixXd group = initializationMatrix(lowerBounds, upperBounds, Population, Dimensions);
//	group = sortMatrixByFitness(group, fitnessFunction);
//
//	std::random_device rd;
//	std::mt19937 gen(rd());
//
//	std::normal_distribution<> disDouble(0.0, 1.0);
//	std::uniform_real_distribution<> disInt(0, (Population/2) - 1);
//
//	for (int Tcurrent = 0;Tcurrent < Tmax; Tcurrent += 1){
//
//		//Teacher allocation
//		Eigen::RowVectorXd avg = (group.row(0) + group.row(1) + group.row(2)) * 3;
//		Eigen::RowVectorXd Teacher = fitnessFunction(group.row(0)) <= fitnessFunction(avg) ? group.row(0) : avg;
//
//		//Ability grouphing phase
//
//		//row.start, col.start, row.size, col.size
//		Eigen::MatrixXd outstandingGroup = group.block(0, 0, int(Population / 2), Dimensions);  
//		Eigen::MatrixXd avarageGroup = group.block(int(Population / 2), 0, int(Population / 2), Dimensions);
//		// TODO
//
//		//Teacher phase for outstandingGroup
//		Eigen::RowVectorXd M = (1 / (Population / 2)) * outstandingGroup.colwise().sum();
//		double a = disDouble(gen);
//		double b = disDouble(gen);
//		double c = 1 - b;
//
//		Eigen::MatrixXd outstandingGroupTeacher(outstandingGroup.rows(), outstandingGroup.cols());
//		for (size_t i = 0; i < outstandingGroupTeacher.rows(); i++){
//			outstandingGroupTeacher.row(i) = outstandingGroup.row(i) + a * (Teacher - 2 * (b * M + outstandingGroup.row(i) * c));
//			outstandingGroupTeacher.row(i) =
//				fitnessFunction(outstandingGroupTeacher.row(i)) < fitnessFunction(outstandingGroup.row(i)) 
//				? outstandingGroupTeacher.row(i) : outstandingGroup.row(i);
//		}
//
//
//		//Teacher phase II for avarageGroup
//		double d = disDouble(gen);
//		Eigen::MatrixXd avarageGroupTeacher(avarageGroup.rows(), avarageGroup.cols());
//		for (size_t i = 0; i < avarageGroupTeacher.rows(); i++){
//			avarageGroupTeacher.row(i) = avarageGroup.row(i) + 1 * d * (Teacher - avarageGroup.row(i));
//			avarageGroupTeacher.row(i) = 
//				fitnessFunction(avarageGroupTeacher.row(i)) < fitnessFunction(avarageGroup.row(i)) 
//				? avarageGroupTeacher.row(i) : avarageGroup.row(i);
//		}
//
//		//Student phase
//		double e = disDouble(gen);
//		double g = disDouble(gen);
//		
//
//		int j = disInt(gen);
//		Eigen::MatrixXd outstandingGroupStudent(outstandingGroup.rows(), outstandingGroup.cols());
//		for (size_t i = 0; i < outstandingGroupStudent.rows(); i++) {
//
//			if (fitnessFunction(outstandingGroupTeacher.row(i)) < fitnessFunction(outstandingGroupTeacher.row(j))){
//				outstandingGroupStudent.row(i) = outstandingGroupTeacher.row(i)
//					+ e * (outstandingGroupTeacher.row(i) - outstandingGroupTeacher.row(j))
//					+ g * (outstandingGroupTeacher.row(i) - outstandingGroup.row(i));
//			}
//			else{
//				outstandingGroupStudent.row(i) = outstandingGroupTeacher.row(i)
//					- e * (outstandingGroupTeacher.row(i) - outstandingGroupTeacher.row(j))
//					+ g * (outstandingGroupTeacher.row(i) - outstandingGroup.row(i));
//			}
//
//			outstandingGroup.row(i) = fitnessFunction(outstandingGroupTeacher.row(i)) < fitnessFunction(outstandingGroupStudent.row(i)) ? outstandingGroupTeacher.row(i) : outstandingGroupStudent.row(i);
//		}
//
//		Eigen::MatrixXd avarageGroupStudent(avarageGroup.rows(), avarageGroup.cols());
//		for (size_t i = 0; i < avarageGroupStudent.rows(); i++) {
//
//			if (fitnessFunction(avarageGroupTeacher.row(i)) < fitnessFunction(avarageGroupTeacher.row(j))) {
//				avarageGroupStudent.row(i) = avarageGroupTeacher.row(i)
//					+ e * (avarageGroupTeacher.row(i) - avarageGroupTeacher.row(j))
//					+ g * (avarageGroupTeacher.row(i) - avarageGroup.row(i));
//			}
//			else {
//				avarageGroupStudent.row(i) = avarageGroupTeacher.row(i)
//					- e * (avarageGroupTeacher.row(i) - avarageGroupTeacher.row(j))
//					+ g * (avarageGroupTeacher.row(i) - avarageGroup.row(i));
//			}
//
//			avarageGroup.row(i) = fitnessFunction(avarageGroupTeacher.row(i)) < fitnessFunction(avarageGroupStudent.row(i)) ? avarageGroupTeacher.row(i) : avarageGroupStudent.row(i);
//		}
//
//		group.resize(outstandingGroup.rows() + avarageGroup.rows(), Dimensions);
//		group << outstandingGroup, avarageGroup;
//		group = sortMatrixByFitness(group, fitnessFunction);
//	}
//	return returnValues(fitnessFunction(group.row(0)), group.row(0));
//}





