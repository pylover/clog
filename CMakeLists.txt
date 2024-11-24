cmake_minimum_required(VERSION 3.7)
project(clog 
    VERSION 1.4.0
    LANGUAGES C
)


set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_GNU_SOURCE=1")


include_directories(
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
)


# Static Library
add_library(clog SHARED clog.c)


# Install
install(TARGETS clog DESTINATION "lib")
install(FILES clog.h DESTINATION "include")


# Uninstall
add_custom_target(uninstall COMMAND xargs rm < install_manifest.txt)


# CPack
set(CPACK_PACKAGE_FILE_NAME "libclog-${PROJECT_VERSION}")
set(CPACK_SET_DESTDIR true)
set(CPACK_PACKAGE_NAME libclog)
set(CPACK_PACKAGE_CONTACT "Vahid Mardani <vahid.mardani@gmail.com>")
set(CPACK_GENERATOR DEB)
include(CPack)

# Examples
add_subdirectory(examples)
