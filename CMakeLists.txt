cmake_minimum_required(VERSION 3.26)
project(labwork5_eklkeklk)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib)
add_subdirectory(bin)

enable_testing()
add_subdirectory(tests)