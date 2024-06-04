cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

project(cpp_compile_time LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

include_directories(../include)

find_package(Catch2 3 REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined -fsanitize=address -Wall")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=undefined -fsanitize=address -Wall")

add_executable(test_cexpr_basic_string test_cexpr_basic_string.cpp)
