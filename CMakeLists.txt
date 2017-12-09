cmake_minimum_required(VERSION 3.7)
project(Diffusion)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")

set(SOURCE_FILES
        main.cpp
        src/core/
        src/module/cipher/
#        src/module/cipher/streams/
        src/module/cipher/algorithms/DC140713AlgorithmFactory.h)

add_executable(Diffusion ${SOURCE_FILES})