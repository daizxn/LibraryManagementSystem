set(BIN_NAME ${CMAKE_PROJECT_NAME})

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find Qt6 packages
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

set(QRC_SOURCE_FILE ${PROJECT_SOURCE_DIR}/resource/res.qrc)
qt_add_resources(QRC_FILES ${QRC_SOURCE_FILE})

file(GLOB_RECURSE SRC_FILES tst_cpp/*.cpp)

add_executable(${BIN_NAME}_tst ${SRC_FILES} main.cpp ${QRC_FILES})
add_test(NAME ${BIN_NAME}_tst COMMAND ${BIN_NAME}_tst)
target_link_libraries(${BIN_NAME} PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)
target_link_libraries(${BIN_NAME}_tst PUBLIC ${BIN_NAME}_lib gtest)

