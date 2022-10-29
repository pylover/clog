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
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)


# Install
install(
    TARGETS clog 
    EXPORT clog
    DESTINATION "lib/clog-${PROJECT_VERSION_MAJOR}")


# CPack
set(CPACK_SET_DESTDIR true)
set(CPACK_PACKAGE_NAME clog)
set(CPACK_PACKAGE_CONTACT "Vahid Mardani <vahid.mardani@gmail.com>")
set(CPACK_GENERATOR DEB)
include(CPack)

# Testing
include(CTest)
list(APPEND CMAKE_CTEST_ARGUMENTS "--output-on-failure")

# CLog test
add_executable(clog_test
    $<TARGET_OBJECTS:clog> 
    clog_test.c)
add_test(NAME clog_test COMMAND clog_test)
