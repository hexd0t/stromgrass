cmake_minimum_required (VERSION 2.6)
project (StromGrass)

include_directories(dep/glm dep/boost)

add_subdirectory(sup)
add_subdirectory(sim)
add_subdirectory(eng)

add_executable(sg main.cpp)
set_property(TARGET sg PROPERTY CXX_STANDARD 14)
set_property(TARGET sg PROPERTY CXX_STANDARD_REQUIRED ON)
target_link_libraries(sg sup sim eng)