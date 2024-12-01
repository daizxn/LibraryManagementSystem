cmake_minimum_required(VERSION 3.28.3)
project(LibraryManagementSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/home/daizxn/Qt/6.8.0/gcc_64")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)
set(QRC_SOURCE_FILE resource/res.qrc)
qt_add_resources(${QRC_SOURCE_FILE})

include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src/view/Headers)

file(GLOB_RECURSE SRC_CPP ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE SRC_H src/view/Headers/*.h)
file(GLOB_RECURSE SRC_UI src/view/Forms/*.ui)
file(GLOB_RECURSE SRC_QtCPP src/view/*.cpp)

add_executable(LibraryManagementSystem main.cpp
        ${SRC_CPP}
        ${SRC_H}
        ${SRC_UI}
        ${SRC_QtCPP}
        ${QRC_SOURCE_FILE}
)
target_link_libraries(LibraryManagementSystem
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

