CMAKE_MINIMUM_REQUIRED(VERSION 3.18)

PROJECT(PLAYGROUND)

SET(PROJECT_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
SET(PLAYGROUND_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
SET(PLAYGROUND_PYSOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/playground")
SET(PLAYGROUND_CMAKE_DIR "${PROJECT_SOURCE_DIR}/cmake")

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
        "${PLAYGROUND_CMAKE_DIR}")

SET(BUILD_SHARED_LIBS true)

## Find Python
FIND_PACKAGE (Python3 COMPONENTS Interpreter Development NumPy)
EXECUTE_PROCESS(COMMAND "${Python3_EXECUTABLE}" -m site --user-site
    OUTPUT_VARIABLE PYTHON_SITE_PACKAGES
    OUTPUT_STRIP_TRAILING_WHITESPACE)
MESSAGE("-- PYTHON_EXECUTABLE: ${Python3_EXECUTABLE}")
MESSAGE("-- PYTHON_SITE_PACKAGES: ${PYTHON_SITE_PACKAGES}")
SET(LIBS ${LIBS} ${Python3_LIBRARIES})


FIND_PACKAGE (Cython)
MESSAGE("-- Found Cython: ${Cython_FOUND}")
MESSAGE(STATUS "Cython Version: ${CYTHON_VERSION}")

# With CMake, a clean separation can be made between the source tree and the
# build tree.  When all source is compiled, as with pure C/C++, the source is
# no-longer needed in the build tree.  However, with pure *.py source, the
# source is processed directly.  To handle this, we reproduce the availability
# of the source files in the build tree.
add_custom_target(ReplicatePythonSourceTree ALL "${CMAKE_COMMAND}" -P
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/ReplicatePythonSourceTree.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}"
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

INCLUDE(UseCython)
INCLUDE_DIRECTORIES("${CMAKE_CURRENT_BINARY_DIR}/playground") # cmake will check this dir for headers

INCLUDE_DIRECTORIES(AFTER "${Python3_INCLUDE_DIRS}")


ADD_SUBDIRECTORY("${PLAYGROUND_SOURCE_DIR}")
ADD_SUBDIRECTORY("${PLAYGROUND_PYSOURCE_DIR}")
ADD_SUBDIRECTORY("${PLAYGROUND_CMAKE_DIR}")