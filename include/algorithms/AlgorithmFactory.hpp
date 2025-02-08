#ifndef ALGORITHM_FACTORY_HPP
#define ALGORITHM_FACTORY_HPP

#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "IAlgorithm.hpp"

class AlgorithmFactory {
 public:
  using CreatorFunction = std::function<IAlgorithm*()>;

  static AlgorithmFactory& Instance();

  void Register(const std::string& name, CreatorFunction creator);

  IAlgorithm* Create(const std::string& name);

 private:
  AlgorithmFactory() = default;
  AlgorithmFactory(const AlgorithmFactory&) = delete;
  AlgorithmFactory& operator=(const AlgorithmFactory&) = delete;

  std::unordered_map<std::string, CreatorFunction> creators;
};

#endif  // ALGORITHM_FACTORY_HPP