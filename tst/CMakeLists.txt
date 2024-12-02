set(BIN_NAME ${CMAKE_PROJECT_NAME})

add_executable(${BIN_NAME}_tst AVLTreeTests.cpp main.cpp)

add_test(NAME ${BIN_NAME}_tst COMMAND ${BIN_NAME}_tst)


target_link_libraries(${BIN_NAME}_tst PUBLIC ${BIN_NAME}_lib gtest)

