cmake_minimum_required(VERSION 3.20)

project(
    Chess
    VERSION 0.1.0
    DESCRIPTION "Chess engine core"
    LANGUAGES CXX
)

option(CHESS_BUILD_TESTS "Build chess tests" ON)

add_subdirectory(src/core)

if(CHESS_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
