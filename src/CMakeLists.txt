# get include directories for cython compiler
set(cython_include_directories "")
get_directory_property(cmake_include_directories
                        DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        INCLUDE_DIRECTORIES)
list(APPEND cython_include_directories ${cmake_include_directories})
list(REMOVE_DUPLICATES cython_include_directories)
set(include_directory_arg "")
foreach(_include_dir ${cython_include_directories})
    set(include_directory_arg ${include_directory_arg} "-I" "${_include_dir}")
endforeach()


# find cython files and compile them
file(GLOB CYCLUS_CORE_CYTHON_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.pyx")
foreach(file ${CYCLUS_CORE_CYTHON_FILES})
    message(STATUS "Cython Compiling ${file}")
    get_filename_component(name ${file} NAME_WE)
    set(_generated_h "${CMAKE_CURRENT_SOURCE_DIR}/${name}.cc.h")
    set(_generated_cc "${CMAKE_CURRENT_SOURCE_DIR}/${name}.cc.gen")
    set(_h_file "${CMAKE_CURRENT_SOURCE_DIR}/${name}.h")
    set(_cc_file "${CMAKE_CURRENT_SOURCE_DIR}/${name}.cc")
    set_source_files_properties(${_cc_file} PROPERTIES GENERATED TRUE)

    EXECUTE_PROCESS(COMMAND ${CYTHON_EXECUTABLE} --cplus
        ${include_directory_arg} -3 --verbose
        --output-file  ${_generated_cc} ${file}
        RESULT_VARIABLE res_var_c)
    IF(NOT "${res_var_c}" STREQUAL "0")
        message(FATAL_ERROR "Cython compilation of ${file} failed!")
    ENDIF()
endforeach()

##### Build libplayground.so

SET(CYCLUS_CORE_INCLUDE_DIRS ${CYCLUS_CORE_INCLUDE_DIRS}
    "${CMAKE_CURRENT_SOURCE_DIR}"
    PARENT_SCOPE
    )
FILE(GLOB cc_files "${CMAKE_CURRENT_SOURCE_DIR}/[^_]*.cc")

FILE(GLOB h_files "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
FILE(GLOB hpp_files "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")
SET(h_files ${h_files} ${hpp_files})
INSTALL(FILES ${h_files} DESTINATION include/playground COMPONENT core)

SET(PLAYGROUND_CORE_SRC ${PLAYGROUND_CORE_SRC} ${cc_files})

ADD_LIBRARY(playground ${PLAYGROUND_CORE_SRC})

SET_TARGET_PROPERTIES(playground
    PROPERTIES
    INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/lib"
    INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib"
)

TARGET_LINK_LIBRARIES(playground dl ${LIBS}) # link against libs we need to link against

INSTALL(
    TARGETS playground
    LIBRARY DESTINATION lib
    COMPONENT playground
)

SET(LIBS ${LIBS} playground PARENT_SCOPE) # add playground to the libs var in the parent scope so that python can access it?