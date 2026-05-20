add_library(
    chess_cli
    parser.cpp
    renderer.cpp
    session.cpp
    repl.cpp
)
add_library(Chess::Cli ALIAS chess_cli)

target_compile_features(chess_cli PUBLIC cxx_std_20)

target_link_libraries(
    chess_cli
    PUBLIC
        Chess::Core
)

target_include_directories(
    chess_cli
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)
