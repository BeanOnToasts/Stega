cmake_minimum_required(VERSION 3.30)
project(Coursework)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 23)

add_executable(Coursework main.cpp
        encrypt/encrypt.h
        encode/encode.h
        encode/encode.cpp
        decode/decode.h
        decode/decode.cpp
        decrypt/decrypt.h
        encrypt/encrypt.cpp
        decrypt/decrypt.cpp)

target_link_libraries(Coursework ${OpenCV_LIBS})