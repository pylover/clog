cmake_minimum_required(VERSION 3.7)
project(clog 
    VERSION 2.0.2
    LANGUAGES C
)


# set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")


include_directories(${PROJECT_SOURCE_DIR})


# target
add_library(clog STATIC clog.c clog.h)


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


# Lint
set(PRETTYC_FLAGS
    --recursive
    --verbose=0
    --repository=.
    --extensions=c,h,in
    --linelength=80
    --headers=h,in
    --includeorder=standardcfirst
    --root=.
    #--quiet
    ${PROJECT_SOURCE_DIR}
)
add_custom_target(lint
    COMMAND prettyc
    ${PRETTYC_FLAGS}
)


# Examples
add_subdirectory(examples)
