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

project(dtkPluginsMetaInfoFetcher)

## #################################################################
## Sources
## #################################################################

set(${PROJECT_NAME}_SOURCES
  main.cpp)

## #################################################################
## Build rules
## #################################################################


add_executable(${PROJECT_NAME}
  ${${PROJECT_NAME}_SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_RPATH 0)
set_target_properties(${PROJECT_NAME} PROPERTIES INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
set_target_properties(${PROJECT_NAME} PROPERTIES INSTALL_RPATH    "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")

target_link_libraries(${PROJECT_NAME}
  dtkCore
  dtkLog)

target_link_libraries(${PROJECT_NAME} Qt5::Core)

## #################################################################
## Source file layout in development environments like Visual Studio
## #################################################################

SOURCE_GROUP("Header Files" REGULAR_EXPRESSION .*\\.h\$)

## #################################################################
## Installation
## #################################################################

install(TARGETS ${PROJECT_NAME}
   BUNDLE DESTINATION bin
  RUNTIME DESTINATION bin)

######################################################################
### CMakeLists.txt ends here


######################################################################
### CMakeLists.txt ends here
