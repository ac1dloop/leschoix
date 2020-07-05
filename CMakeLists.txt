cmake_minimum_required(VERSION 3.0)

project(leschoix)
set(CMAKE_CXX_STANDARD 11)

enable_testing()
set(TEST leschoix)

add_executable(${TEST} "main.cpp")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

if(UNIX)
    set(INSTALL_PATH "/usr/local/include")
endif(UNIX)

install(FILES "leschoix.hpp" DESTINATION ${INSTALL_PATH})

message(${CMAKE_CURRENT_BINARY_DIR})

add_test(NAME is_compiling COMMAND ${TEST})
add_test(NAME arg_to_bool_dash COMMAND ${TEST} -v)
add_test(NAME arg_to_bool_double_dash COMMAND ${TEST} --version)
add_test(NAME arg_to_uint16t_space COMMAND ${TEST} -p 8080)
add_test(NAME arg_to_uint16t_eq COMMAND ${TEST} -p=8080)
add_test(NAME arg_to_uint16t_long_space COMMAND ${TEST} --port 8080)
add_test(NAME arg_to_uint16t_long_eq COMMAND ${TEST} --port=8080)
