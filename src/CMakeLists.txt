
file(GLOB UI_HEADERS "${CMAKE_SOURCE_DIR}/include/ui/*.hpp")
qt6_wrap_cpp(MOC_SOURCES ${UI_HEADERS})

add_library(mainsrc STATIC
    ui/Window.cpp
    ui/AlgorithmList.cpp
    ui/AlgorithmListItem.cpp
    ui/BenchmarkDialog.cpp
    ui/AlgorithmData.cpp
    ui/Benchmark.cpp
    algorithms/dllHandler.cpp
    algorithms/AlgorithmFactory.cpp
    ${MOC_SOURCES}
)

target_link_libraries(mainsrc PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)

target_include_directories(mainsrc PUBLIC "${CMAKE_SOURCE_DIR}/include" ${Qt6_INCLUDE_DIRS})

add_executable(main main.cpp)

target_link_libraries(main PRIVATE mainsrc Qt6::Core Qt6::Gui Qt6::Widgets)

target_compile_options(main PRIVATE -Wall -Wextra -Wshadow -Wconversion -Wpedantic -Werror --debug)
