cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

project(cpp_compile_time LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

find_package(Catch2 3 REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -gdwarf-4 -fsanitize=address -Wall")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lstdc++ -fsanitize=address -Wall")

if (${CMAKE_CXX_COMPILER} STREQUAL "gcc")
    set(EXTRA_COMPILE_FLAGS "-fconstexpr-loop-limit=10000 -fconstexpr-ops-limit=1000000000")
else()
    set(EXTRA_COMPILE_FLAGS "-fconstexpr-steps=100000000")
endif()

set_source_files_properties(app/test_mandelbrot.cpp PROPERTIES COMPILE_FLAGS ${EXTRA_COMPILE_FLAGS})

add_executable(test_cexpr_basic_string app/test_cexpr_basic_string.cpp)
target_link_libraries(test_cexpr_basic_string Catch2::Catch2WithMain)

add_executable(test_mandelbrot app/test_mandelbrot.cpp)
target_link_libraries(test_mandelbrot Catch2::Catch2WithMain)
