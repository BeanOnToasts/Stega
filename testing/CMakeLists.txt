cmake_minimum_required(VERSION 3.30)
project(13764108_IPA_A1_testing)

find_package(OpenCV REQUIRED)
find_package(GTest REQUIRED)

set(CMAKE_PREFIX_PATH "C:/Qt/6.8.2/msvc2022_64")
find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)

set(CMAKE_CXX_STANDARD 23)

add_executable(13764108_IPA_A1_testing test_main.cpp
        test_encoder.cpp
        ../encode/encode.cpp
        test_decoder.cpp
        ../decode/decode.cpp
)

target_link_libraries(13764108_IPA_A1_testing ${OpenCV_LIBS}
        ${GTEST_LIBRARIES}
        ${GTEST_MAIN_LIBRARIES}
        Qt::Core
        Qt::Gui
        Qt::Widgets)