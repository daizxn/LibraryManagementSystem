cmake_minimum_required(VERSION 3.28.3)
project(LibraryManagementSystem)

set(CMAKE_CXX_STANDARD 17)


include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src/view/Headers)


add_subdirectory(src)
add_subdirectory(tst)
add_subdirectory(lib/googletest)