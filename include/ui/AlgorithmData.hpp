#ifndef ALGORITHMDATA_HPP
#define ALGORITHMDATA_HPP

#include <filesystem>
#include <functional>
#include <string>
#include <vector>

#include "../algorithms/dllHandler.hpp"

class AlgorithmData {
 private:
  std::string name = "";
  std::filesystem::path path;
  std::vector<ParamInfo> params;

  DLLHandler dllHandler;

 public:
  AlgorithmData(std::filesystem::path path);

  // Getters
  std::string getName() const;
  std::string getPath() const;
  std::vector<ParamInfo> getParams() const;
  // Setters
  void addParams(ParamInfo param);
  void removeParams(size_t index);
};

#endif  // ALGORITHMDATA_HPP