cmake_minimum_required(VERSION 3.22)
project(2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-O3")
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(2 2.cpp)
target_link_libraries(2 ${OpenCV_LIBS})