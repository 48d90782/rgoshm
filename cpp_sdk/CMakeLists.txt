cmake_minimum_required(VERSION 3.18 FATAL_ERROR)
project(shm)

set(CMAKE_CXX_STANDARD 20)
enable_language(CXX C)

find_package(Boost 1.73)
find_path(BOOST_INTERPROCESS_INCLUDE_DIRS "boost/interprocess/allocators/adaptive_pool.hpp")
include_directories(${BOOST_INTERPROCESS_INCLUDE_DIRS})

file(GLOB _process1 src/first.cpp src/first.h src/shared_data.h)
file(GLOB _process2 src/second.cpp src/second.h src/shared_data.h)
file(GLOB goshm src/rgoshm.cpp src/rgoshm.h src/shared_data.h)

add_executable(process1 ${_process1})
target_link_libraries(process1 ${Boost_LIBRARIES} pthread rt)

add_executable(process2 ${_process2})
target_link_libraries(process2 ${Boost_LIBRARIES} pthread rt)

add_library(${CMAKE_PROJECT_NAME} SHARED ${goshm})
target_link_libraries(${CMAKE_PROJECT_NAME} ${Boost_LIBRARIES} pthread rt)
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory ../../../lib
        COMMAND ${CMAKE_COMMAND} -E copy libshm.so ../../../lib)