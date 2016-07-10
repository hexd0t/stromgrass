set(sim_src staticenv.h staticenv.cpp glm_boostpolygon.h)

add_library(sim ${sim_src})
set_property(TARGET sim PROPERTY CXX_STANDARD 14)
set_property(TARGET sim PROPERTY CXX_STANDARD_REQUIRED ON)