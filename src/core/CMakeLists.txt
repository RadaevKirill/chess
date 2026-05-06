add_library(chess_core INTERFACE)
add_library(Chess::Core ALIAS chess_core)

target_compile_features(chess_core INTERFACE cxx_std_20)

target_include_directories(
    chess_core
    INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)
