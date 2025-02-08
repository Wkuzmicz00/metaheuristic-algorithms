#include "../include/ui/AlgorithmData.hpp"

#include <iostream>
AlgorithmData::AlgorithmData(std::filesystem::path filePath) {
  name = filePath.filename();
  path = std::filesystem::current_path() / filePath;
  dllHandler.Load(filePath);
}

std::string AlgorithmData::getName() const { return name; }
std::string AlgorithmData::getPath() const { return path; }
std::vector<ParamInfo> AlgorithmData::getParams() const { return params; }

void AlgorithmData::addParams(ParamInfo param) { params.push_back(param); }
void AlgorithmData::removeParams(size_t index) {
  params.erase(params.begin() + index);
}
