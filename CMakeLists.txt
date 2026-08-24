cmake_minimum_required(VERSION 3.14)
project(MetroApp VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)

# Main application
add_executable(metro_app
    src/main.cpp
    src/Station.cpp
    src/Graph.cpp
    src/RoutePlanner.cpp
    src/MetroSystem.cpp
)

# Test executable
add_executable(test_metro
    tests/test_routes.cpp
    src/Station.cpp
    src/Graph.cpp
    src/RoutePlanner.cpp
)

# Enable testing
enable_testing()
add_test(NAME MetroTests COMMAND test_metro)
