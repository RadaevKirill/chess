cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(
    Chess
    VERSION 0.1.0
    DESCRIPTION "Chess engine core"
    LANGUAGES CXX
)

option(CHESS_BUILD_TESTS "Build chess tests" ON)

add_subdirectory(src/core)
add_subdirectory(src/cli)
add_subdirectory(src/app)

# Финальный исполняемый файл — собирает всё вместе
add_executable(chess_game main.cpp)
target_link_libraries(chess_game PRIVATE Chess::App)

if(CHESS_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
