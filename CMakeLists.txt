cmake_minimum_required(VERSION 3.7)
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


# Static Library
add_library(clog STATIC clog.c)


# Install
install(TARGETS clog DESTINATION "lib")
install(FILES clog.h DESTINATION "include")


# CPack
set(CPACK_PACKAGE_FILE_NAME "libclog-${PROJECT_VERSION}")
set(CPACK_SET_DESTDIR true)
set(CPACK_PACKAGE_NAME libclog)
set(CPACK_PACKAGE_CONTACT "Vahid Mardani <vahid.mardani@gmail.com>")
set(CPACK_GENERATOR DEB)
include(CPack)
