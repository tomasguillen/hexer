cmake_minimum_required(VERSION 3.18)
project(Hexer VERSION 0.1.0 LANGUAGES C CXX)

add_library(Hexer INTERFACE)
target_sources(Hexer INTERFACE hexer.hpp)
target_include_directories(Hexer INTERFACE .)
#target_compile_features(Hexer INTERFACE cxx_std_20)
