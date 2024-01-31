INCLUDE_DIRECTORIES(${PLAYGROUND_CORE_INCLUDE_DIRS})

file(GLOB PLAYGROUND_CYTHON_FILES "${PLAYGROUND_PYSOURCE_DIR}/*.pyx")

set_source_files_properties(${PLAYGROUND_CYTHON_FILES}
    PROPERTIES CYTHON_IS_CXX TRUE)

# Print include dir
get_property(inc_dirs DIRECTORY PROPERTY INCLUDE_DIRECTORIES)
message("-- Include paths for ${CMAKE_CURRENT_SOURCE_DIR}: ${inc_dirs}")

# compile cython
foreach(file ${PLAYGROUND_CYTHON_FILES})
    get_filename_component(name ${file} NAME_WE)
    set(targ "py_${name}_")
    cython_add_module(${targ} ${file})
    MESSAGE("LIBS ${LIBS}")
    target_link_libraries(${targ} PRIVATE dl ${LIBS})
    set_target_properties(${targ} PROPERTIES LINKER_LANGUAGE CXX
                                             OUTPUT_NAME ${name}
                                             LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
    # the following install is needed so that CMake sets the correct RPATH for the
    # python extension modules, even though they are installed (with the wrong RPATH)
    # by setup.py, along with the pure python files.
    # install(TARGETS ${targ} LIBRARY DESTINATION "${PYTHON_SITE_PACKAGES}/cyclus")
endforeach()