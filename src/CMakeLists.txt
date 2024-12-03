
# Set binary and project name
set(BIN_NAME ${CMAKE_PROJECT_NAME})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)


# Enable Qt's automatic features (MOC, RCC, UIC)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Specify the Qt installation directory (if not already detected)
set(CMAKE_PREFIX_PATH "/home/daizxn/Qt/6.8.0/gcc_64")

# Find Qt6 packages
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# Define resource file (QRC)
set(QRC_SOURCE_FILE ${PROJECT_SOURCE_DIR}/resource/res.qrc)
qt_add_resources(QRC_FILES ${QRC_SOURCE_FILE})

# Gather source files
file(GLOB_RECURSE SRC_CPP ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE SRC_H ${PROJECT_SOURCE_DIR}/src/view/Headers/*.h)
file(GLOB_RECURSE SRC_UI ${PROJECT_SOURCE_DIR}/src/view/Forms/*.ui)
file(GLOB_RECURSE SRC_QtCPP ${PROJECT_SOURCE_DIR}/src/view/*.cpp)

# Add executable target (with Qt-specific features)
qt_add_executable(${BIN_NAME}
        main.cpp
        ${SRC_CPP}
        ${SRC_H}
        ${SRC_UI}
        ${SRC_QtCPP}
        ${QRC_FILES}  # Include resources in the executable
)

# Link Qt libraries to the executable
target_link_libraries(${BIN_NAME} PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)

# Add static library target
add_library(${BIN_NAME}_lib STATIC
        ${SRC_CPP}
        ${SRC_H}
        ${SRC_UI}
        ${SRC_QtCPP}
        ${QRC_FILES}  # Include resources in the static library
)

# Link Qt libraries to the static library
target_link_libraries(${BIN_NAME}_lib PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)

# Ensure proper include directories (Qt headers)
target_include_directories(${BIN_NAME}_lib PUBLIC ${Qt6Core_INCLUDE_DIRS})
target_include_directories(${BIN_NAME} PUBLIC ${Qt6Core_INCLUDE_DIRS})