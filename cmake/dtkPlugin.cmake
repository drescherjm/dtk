### dtkPlugin.cmake --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Wed Apr  7 09:09:18 2010 (+0200)
## Version: $Id$
## Last-Updated: Thu Nov 17 15:49:07 2011 (+0100)
##           By: Julien Wintz
##     Update #: 19
######################################################################
## 
### Commentary: This script overrides some of the dtkBuild script
#               variables to match the excpected plugin layout.
## 
######################################################################
## 
### Change log:
## 
######################################################################

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins/)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins/)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin/)

add_definitions(${QT_DEFINITIONS})
add_definitions(-DQT_PLUGIN)
add_definitions(-DQT_SHARED)
if(NOT MSVC)
  add_definitions(-DQT_NO_DEBUG)
endif(NOT MSVC)

macro(dtk_build_doc plugin)
  find_package(Doxygen QUIET)
  if (DOXYGEN_FOUND)
    configure_file(${plugin}.doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/${plugin}.doxyfile IMMEDIATE @ONLY)
    configure_file(${plugin}.qhcp.in ${CMAKE_CURRENT_BINARY_DIR}/${plugin}.qhcp IMMEDIATE @ONLY)

    add_custom_target(${PROJECT_NAME}Documentation
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      COMMAND ${DOXYGEN_EXECUTABLE} ${plugin}.doxyfile
      COMMAND qhelpgenerator html/index.qhp -o ${plugin}.qch
      COMMAND qcollectiongenerator ${plugin}.qhcp -o ${plugin}.qhc
      COMMENT "-- Generating embedded documentation")
  endif (DOXYGEN_FOUND)
endmacro(dtk_build_doc)
