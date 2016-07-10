set(eng_src engine.cpp engine.h)

add_library(eng ${eng_src})
set_property(TARGET eng PROPERTY CXX_STANDARD 14)
set_property(TARGET eng PROPERTY CXX_STANDARD_REQUIRED ON)