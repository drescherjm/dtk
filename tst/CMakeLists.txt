## Version: $Id$
##
######################################################################
##
### Commentary:
##
######################################################################
##
### Change Log:
##
######################################################################
##
### Code:

configure_file(${CMAKE_SOURCE_DIR}/cmake/dtkSetTestEnvironment.cmake.in "${CMAKE_BINARY_DIR}/dtkSetTestEnvironment.cmake" @ONLY)

set_directory_properties(PROPERTIES TEST_INCLUDE_FILE "${CMAKE_BINARY_DIR}/dtkSetTestEnvironment.cmake")

add_subdirectory(dtkCore)
#add_subdirectory(dtkComposer)
add_subdirectory(dtkLog)
add_subdirectory(dtkMeta)
add_subdirectory(dtkMath)

######################################################################
### CMakeLists.txt ends here
