set(sup_src log.h log.cpp log.inl.h)

add_library(sup ${sup_src})
set_property(TARGET sup PROPERTY CXX_STANDARD 14)
set_property(TARGET sup PROPERTY CXX_STANDARD_REQUIRED ON)