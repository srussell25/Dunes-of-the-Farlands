cmake_minimum_required(VERSION 3.19)

project(fall2023-csc3380-project)

set(CMAKE_CXX_STANDARD 20)

enable_testing()
include(CTest)

add_executable(project code/main.cpp)
add_executable(runtests code/runtests.cpp)

target_compile_definitions(runtests PRIVATE CATCH_CONFIG_MAIN)
add_test(NAME runtests COMMAND runtests WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})