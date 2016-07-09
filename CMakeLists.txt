cmake_minimum_required (VERSION 2.6)
project (StromGrass)

add_subdirectory(sup)
add_subdirectory(sim)
add_subdirectory(eng)

add_executable(sg main.cpp)
target_link_libraries(sg sup sim eng)