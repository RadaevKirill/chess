add_library(
    chess_core
    board.cpp
    history.cpp
)
add_library(Chess::Core ALIAS chess_core)

target_compile_features(chess_core PUBLIC cxx_std_20)

target_include_directories(
    chess_core
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)
