find_package(GTest CONFIG QUIET)

if(NOT GTest_FOUND)
    message(STATUS "GoogleTest was not found. Test targets will be added after GoogleTest is available.")
    return()
endif()

add_subdirectory(core)
