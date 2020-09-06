cmake_minimum_required(VERSION 3.18 FATAL_ERROR)
project(shm)

set(CMAKE_CXX_STANDARD 20)
enable_language(CXX C)

find_package(Boost 1.73)
find_path(BOOST_INTERPROCESS_INCLUDE_DIRS "boost/interprocess/allocators/adaptive_pool.hpp")
include_directories(${BOOST_INTERPROCESS_INCLUDE_DIRS})

file(GLOB _src src/*.cpp src/*.h include/*.h)

add_executable(${CMAKE_PROJECT_NAME} ${_src})
target_link_libraries(${CMAKE_PROJECT_NAME} ${Boost_LIBRARIES} rt)