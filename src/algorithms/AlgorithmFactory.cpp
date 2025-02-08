#include "../include/algorithms/AlgorithmFactory.hpp"

#include <iostream>

AlgorithmFactory& AlgorithmFactory::Instance() {
  static AlgorithmFactory instance;
  return instance;
}

void AlgorithmFactory::Register(const std::string& name,
                                CreatorFunction creator) {
  creators[name] = creator;
}

IAlgorithm* AlgorithmFactory::Create(const std::string& name) {
  auto it = creators.find(name);
  if (it != creators.end()) {
    return it->second();
  }
  throw std::invalid_argument("Algorithm not found: " + name);
}
