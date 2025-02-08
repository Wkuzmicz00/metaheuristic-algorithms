#include <QApplication>

#include "../include/algorithms/iwo.cpp"
#include "../include/ui/Window.hpp"

// double sphere(const std::vector<double>& x) {
//   double sum = 0.0;
//   for (double xi : x) {
//     sum += xi * xi;
//   }
//   return sum;
// }

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);

  Window w(nullptr, "Metaheuristic algorithms benchmark");
  w.show();

  return a.exec();
  // DLLHandler dll;
  // dll.Load("/home/wojtek/Desktop/libInverseWeedOptimizer.so");

  // IAlgorithm* algorithm =
  //     AlgorithmFactory::Instance().Create("libInverseWeedOptimizer.so");

  // algorithm->Solve(sphere);
};