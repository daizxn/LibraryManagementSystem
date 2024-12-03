set(BIN_NAME ${CMAKE_PROJECT_NAME})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

file(GLOB_RECURSE SRC_FILES tst_cpp/*.cpp)

add_executable(${BIN_NAME}_tst ${SRC_FILES} main.cpp)
add_test(NAME ${BIN_NAME}_tst COMMAND ${BIN_NAME}_tst)

target_link_libraries(${BIN_NAME}_tst PUBLIC ${BIN_NAME}_lib gtest)

