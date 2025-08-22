cmake_minimum_required(VERSION 3.7)
project(clog 
    VERSION 2.0.1
    LANGUAGES C
)


include_directories(${PROJECT_SOURCE_DIR})


# Static Library
add_library(clog STATIC clog.c)


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
