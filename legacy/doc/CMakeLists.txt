### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Tue Feb  2 20:18:37 2010 (+0100)
## Version: $Id$
## Last-Updated: Tue Nov  8 17:36:39 2011 (+0100)
##           By: Julien Wintz
##     Update #: 47
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

## #################################################################
## Retrieve dependencies
## #################################################################

set(Doxygen_FIND_QUIETLY TRUE)

find_package(Doxygen)

## #################################################################
## Build rules
## #################################################################

if (DOXYGEN_FOUND)
  configure_file(Doxyfile.in     ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile IMMEDIATE @ONLY)
  configure_file(qhc/dtk.qhcp.in ${CMAKE_CURRENT_BINARY_DIR}/dtk.qhcp IMMEDIATE @ONLY)

  add_custom_target(${PROJECT_NAME}-doc
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/DoxygenLayout.xml  ${CMAKE_CURRENT_BINARY_DIR}/DoxygenLayout.xml
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/DoxygenHeader.html ${CMAKE_CURRENT_BINARY_DIR}/DoxygenHeader.html
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/DoxygenFooter.html ${CMAKE_CURRENT_BINARY_DIR}/DoxygenFooter.html
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/img      ${CMAKE_CURRENT_BINARY_DIR}/html/img
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/css      ${CMAKE_CURRENT_BINARY_DIR}/html/css
    COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile
    COMMAND ${QT_BINARY_DIR}/qhelpgenerator html/index.qhp -o dtk.qch
    COMMAND ${QT_BINARY_DIR}/qcollectiongenerator dtk.qhcp -o dtk.qhc
    COMMENT "-- Generating embedded documentation")

  if(EXISTS ${CMAKE_BINARY_DIR}/doc/dtk.qhc)
    install(FILES ${CMAKE_BINARY_DIR}/doc/dtk.qhc DESTINATION doc)
  endif(EXISTS ${CMAKE_BINARY_DIR}/doc/dtk.qhc)

  if(EXISTS ${CMAKE_BINARY_DIR}/doc/html)
    install(DIRECTORY ${CMAKE_BINARY_DIR}/doc/html DESTINATION doc)
  endif(EXISTS ${CMAKE_BINARY_DIR}/doc/html)
endif (DOXYGEN_FOUND)
