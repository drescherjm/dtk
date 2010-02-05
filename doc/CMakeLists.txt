### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Tue Feb  2 20:18:37 2010 (+0100)
## Version: $Id$
## Last-Updated: Fri Feb  5 12:59:46 2010 (+0100)
##           By: Julien Wintz
##     Update #: 18
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

project(documentation)

## #################################################################
## Retrieve dependencies
## #################################################################

set(DOXYGEN_FIND_QUIETLY TRUE)

find_package(Doxygen)

## #################################################################
## Build rules
## #################################################################

if (DOXYGEN_FOUND)
  configure_file(Doxyfile.config.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile IMMEDIATE @ONLY)
  configure_file(dtk.qhcp.in ${CMAKE_CURRENT_BINARY_DIR}/dtk.qhcp IMMEDIATE @ONLY)

  add_custom_target(doc
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/DoxygenLayout.xml  ${CMAKE_CURRENT_BINARY_DIR}/DoxygenLayout.xml
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/DoxygenHeader.html ${CMAKE_CURRENT_BINARY_DIR}/DoxygenHeader.html
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/DoxygenFooter.html ${CMAKE_CURRENT_BINARY_DIR}/DoxygenFooter.html
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/DoxygenStyle.css   ${CMAKE_CURRENT_BINARY_DIR}/DoxygenStyle.css
    COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile
    COMMAND ${CMAKE_COMMAND} -E remove qch/dtk-0.1.qch
    COMMAND qhelpgenerator html/index.qhp -o dtk.qch
    COMMAND qcollectiongenerator dtk.qhcp -o dtk.qhc
    COMMENT "-- Generating embedded documentation"
    )
else (DOXYGEN_FOUND)
  message(INFO "Can't find doxygen. Can't build documentation")
endif (DOXYGEN_FOUND)
