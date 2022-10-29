cmake_minimum_required(VERSION 3.10)
project(clog 
    VERSION 1.0.0
    LANGUAGES C
)
configure_file(manifest.h.in manifest.h)


set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_GNU_SOURCE=1")


include_directories(
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
)


add_library(clog OBJECT clog.c)


# Testing
include(CTest)
list(APPEND CMAKE_CTEST_ARGUMENTS "--output-on-failure")

# CLog test
add_executable(clog_test
    $<TARGET_OBJECTS:clog> 
    clog_test.c)
add_test(NAME clog_test COMMAND clog_test)
