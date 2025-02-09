cmake_minimum_required(VERSION 3.30)
project(minmax_testing)

set(CMAKE_CXX_STANDARD 20)

add_executable(minmax_testing main.cpp misere.h 5x5X_O.h
        misereAI.h)
