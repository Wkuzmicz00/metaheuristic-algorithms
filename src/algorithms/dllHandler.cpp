#include "../include/algorithms/dllHandler.hpp"

#include <iostream>

void DLLHandler::Load(std::filesystem::path filePath) {
  using CreateFunc = IAlgorithm* (*)();
  std::filesystem::path Path = std::filesystem::current_path() / filePath;

#ifdef _WIN32
  _hModule = LoadLibrary(Path.c_str());
  if (!_hModule) {
    throw std::runtime_error(
        "An error occurred: unable to load library on Windows");
  }

  CreateFunc Create =
      reinterpret_cast<CreateFunc>(GetProcAddress(hModule, "Create"));
  if (!Create) {
    FreeLibrary(hModule);
    throw std::runtime_error(
        "Failed to load Create function from library on Windows");
  }

#elif __linux__
  _hModule = dlopen(Path.c_str(), RTLD_LAZY);
  std::cout << "XD";
  if (!_hModule) {
    std::cerr << "dlopen failed: " << dlerror() << std::endl;
    std::cerr << "Failed to load library from path: " << Path.c_str()
              << std::endl;
    return;
  }
  CreateFunc Create = reinterpret_cast<CreateFunc>(dlsym(_hModule, "Create"));
  if (!Create) {
    dlclose(_hModule);
    std::cerr << "dlopen failed: " << dlerror() << std::endl;
    std::cerr << "Failed to load function from path: " << Path.c_str()
              << std::endl;
    return;
  }
#endif
  // TODO sprawdz czy sciezka jest poprawna
  AlgorithmFactory::Instance().Register(Path.filename(), Create);
}

DLLHandler::~DLLHandler() {
#ifdef _WIN32
  FreeLibrary(_hModule);
#else
  if (_hModule) dlclose(_hModule);
#endif
}