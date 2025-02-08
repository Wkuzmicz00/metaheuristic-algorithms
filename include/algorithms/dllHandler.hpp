#ifdef _WIN32
#include <windows.h>
#elif __linux__
#include <dlfcn.h>
#endif

#include <filesystem>
#include <stdexcept>

#include "AlgorithmFactory.hpp"
#include "IAlgorithm.hpp"

class DLLHandler {
 public:
  DLLHandler() = default;
  ~DLLHandler();

  void Load(std::filesystem::path filePath);

 private:
#ifdef _WIN32
  MODULE _hModule;
#elif __linux__
  void* _hModule;
#endif
};
