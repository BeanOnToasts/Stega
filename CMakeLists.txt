cmake_minimum_required(VERSION 3.30)
project(Coursework)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 23)

add_executable(Coursework main.cpp
        encryption.h)

target_link_libraries(Coursework ${OpenCV_LIBS})