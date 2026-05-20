add_library(chess_app main.cpp)
add_library(Chess::App ALIAS chess_app)

target_compile_features(chess_app PUBLIC cxx_std_20)

target_link_libraries(
    chess_app
    PUBLIC
        Chess::Cli
)

target_include_directories(
    chess_app
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)
