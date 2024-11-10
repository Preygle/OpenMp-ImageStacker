cmake_minimum_required(VERSION 3.10)

project(cpp)

# Find OpenCV package
set(OpenCV_DIR C:/opencv/build)

find_package(OpenCV REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp)
# Include directories from OpenCV

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
# Create an executable


# Link OpenCV libraries

#include_directories(${OpenCV_INCLUDE_DIRS}) 