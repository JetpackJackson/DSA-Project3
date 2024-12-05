cmake_minimum_required(VERSION 3.28)
project(dsa_final)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include the 'include' directory for header files
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/tests)
include_directories(${CMAKE_SOURCE_DIR}/lib)

file(COPY ${CMAKE_SOURCE_DIR}/src/data.csv DESTINATION ${CMAKE_BINARY_DIR})


# Define the executable
add_executable(dsa_final
        src/main.cpp
        "src/Dijkstra's Algoritm.cpp"
        "src/Build Graph.cpp"
        "src/Bellman Ford Algorithm.cpp")

# Link ws2_32 for HTTP functionality on Windows
target_link_libraries(dsa_final PRIVATE ws2_32)


