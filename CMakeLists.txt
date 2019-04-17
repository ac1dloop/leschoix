cmake_minimum_required(VERSION 2.8)

project(leschoix)
add_executable(${PROJECT_NAME} "examples/handler.cpp")

add_executable("simple_test" "examples/main.cpp")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "./bin")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 11)
