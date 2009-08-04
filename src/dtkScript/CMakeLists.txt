### CMakeLists.txt --- 
## 
## Author: Jean-Christophe Lombardo
## Copyright (C) 2008-2009 - Jean-Christophe Lombardo, Inria.
## Created: Tue Mar 10 15:12:38 2009 (+0100)
## Version: $Id$
## Last-Updated: Tue Aug  4 21:31:02 2009 (+0200)
##           By: Julien Wintz
##     Update #: 24
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

project(dtkScript)

## #################################################################
## Sources
## #################################################################

set(${PROJECT_NAME}_HEADERS
  dtkScriptInterpreter.h
  dtkScriptInterpreterPool.h
  dtkScriptInterpreterPython.h
  dtkScriptInterpreterTcl.h
  dtkScriptManager.h
)

set(${PROJECT_NAME}_HEADERS_MOC
  dtkScriptInterpreter.h
  dtkScriptInterpreterPool.h
  dtkScriptInterpreterPython.h
  dtkScriptInterpreterTcl.h
  dtkScriptManager.h
)

set(${PROJECT_NAME}_SOURCES
  dtkScriptInterpreter.cpp
  dtkScriptInterpreterPool.cpp
  dtkScriptInterpreterPython.cpp
  dtkScriptInterpreterTcl.cpp
  dtkScriptManager.cpp
)

## #################################################################
## Resolve dependencies
## #################################################################

mark_as_advanced(EDITLINE_INCLUDE_DIR)
mark_as_advanced(EDITLINE_LIBRARY)

find_path(EDITLINE_INCLUDE_DIR histedit.h
  /usr/include
  /usr/local/include
)

find_library(EDITLINE_LIBRARY edit
  /usr/lib
  /usr/local/lib
)

if(EDITLINE_LIBRARY)
  set(EDITLINE_FOUND "YES")
endif(EDITLINE_LIBRARY)

if(EDITLINE_FOUND)
  add_definitions(-DHAVE_EDITLINE)
endif(EDITLINE_FOUND)

## #################################################################
## Build rules
## #################################################################

qt4_wrap_cpp(${PROJECT_NAME}_SOURCES_MOC ${${PROJECT_NAME}_HEADERS_MOC})

add_library(${PROJECT_NAME}
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_SOURCES_MOC}
)

target_link_libraries(${PROJECT_NAME}
  ${TCL_LIBRARY}
  ${QT_LIBRARIES}
  dtkCore
)

if(PYTHON_DEBUG_LIBRARIES)
  target_link_libraries(${PROJECT_NAME} debug ${PYTHON_DEBUG_LIBRARIES})
  target_link_libraries(${PROJECT_NAME} optimized ${PYTHON_LIBRARIES})
else(PYTHON_DEBUG_LIBRARIES)
  target_link_libraries(${PROJECT_NAME} ${PYTHON_LIBRARIES})
endif(PYTHON_DEBUG_LIBRARIES)

if(EDITLINE_FOUND)
  target_link_libraries(${PROJECT_NAME} ${EDITLINE_LIBRARY})
endif(EDITLINE_FOUND)

## #################################################################
## Installation
## #################################################################

if(NOT dtk_INSTALL_NO_DEVELOPMENT)
  install_files(${dtk_INSTALL_INCLUDE_DIR}/${PROJECT_NAME} .h ${${PROJECT_NAME}_HEADERS})
endif(NOT dtk_INSTALL_NO_DEVELOPMENT)

if(NOT dtk_INSTALL_NO_LIBRARIES)
  install_targets(${dtk_INSTALL_LIB_DIR} RUNTIME_DIRECTORY ${dtk_INSTALL_BIN_DIR} ${PROJECT_NAME})
endif(NOT dtk_INSTALL_NO_LIBRARIES)
