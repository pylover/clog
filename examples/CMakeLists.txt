list(APPEND examples
  quickstart
  showcase
)


foreach (t IN LISTS examples) 
    # Test help
    add_executable(${t} 
        ${t}.c
        $<TARGET_OBJECTS:clog>
    )
    target_include_directories(${t} PUBLIC "${PROJECT_BINARY_DIR}")
    add_custom_target(${t}_exec 
        COMMAND ./${t}
        DEPENDS ${t}
      )
    add_custom_target(${t}_profile
        COMMAND "valgrind" ${VALGRIND_FLAGS} ./${t}
        DEPENDS ${t}
    )
endforeach()
