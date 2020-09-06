cmake_minimum_required(VERSION 3.18 FATAL_ERROR)
project(shm)

set(CMAKE_CXX_STANDARD 20)
enable_language(CXX C)

file(GLOB _src src/*.cpp src/*.h include/*.h)

add_executable(${CMAKE_PROJECT_NAME} ${_src})