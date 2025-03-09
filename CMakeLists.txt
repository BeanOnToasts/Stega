cmake_minimum_required(VERSION 3.30)
project(Coursework)

find_package(OpenCV REQUIRED)

set(Qt6_DIR "C:/Qt/6.8.2/msvc2022_64/lib/cmake/Qt6") #wouldn't work without this
find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_PREFIX_PATH "C:/Qt/6.8.2/msvc2022_64")

add_executable(Coursework main.cpp
        encrypt/encrypt.h
        encode/encode.h
        encode/encode.cpp
        decode/decode.h
        decode/decode.cpp
        decrypt/decrypt.h
        encrypt/encrypt.cpp
        decrypt/decrypt.cpp
        GUI/selectOption.cpp
        GUI/selectOption.h
        GUI/encodeWindow.cpp
        GUI/encodeWindow.h
        GUI/decodeWindow.cpp
        GUI/decodeWindow.h)

target_link_libraries(Coursework ${OpenCV_LIBS} Qt::Core Qt::Gui Qt::Widgets)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()

    #added this but it didnt fix it
    if (NOT DEFINED CMAKE_PREFIX_PATH)
        set(CMAKE_PREFIX_PATH "C:/Qt/6.8.2/msvc2022_64/lib/cmake")
    endif ()

    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")

    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()

    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()

    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()