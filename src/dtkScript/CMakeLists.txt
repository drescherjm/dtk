### CMakeLists.txt --- 
## 
## Author: Jean-Christophe Lombardo
## Copyright (C) 2008-2009 - Jean-Christophe Lombardo, Inria.
## Created: Tue Mar 10 15:12:38 2009 (+0100)
## Version: $Id$
## Last-Updated: Mon Apr 26 13:13:32 2010 (+0200)
##           By: Julien Wintz
##     Update #: 38
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
  dtkScriptManager.h)

set(${PROJECT_NAME}_HEADERS_MOC
  dtkScriptInterpreter.h
  dtkScriptInterpreterPool.h
  dtkScriptInterpreterPython.h
  dtkScriptInterpreterTcl.h
  dtkScriptManager.h)

set(${PROJECT_NAME}_SOURCES
  dtkScriptInterpreter.cpp
  dtkScriptInterpreterPool.cpp
  dtkScriptInterpreterPython.cpp
  dtkScriptInterpreterTcl.cpp
  dtkScriptManager.cpp)

## #################################################################
## Build rules
## #################################################################

add_definitions(${QT_DEFINITIONS})
add_definitions(-DQT_SHARED)
add_definitions(-DQT_NO_DEBUG)

qt4_wrap_cpp(${PROJECT_NAME}_SOURCES_MOC ${${PROJECT_NAME}_HEADERS_MOC})

add_library(${PROJECT_NAME} SHARED
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_SOURCES_MOC})

target_link_libraries(${PROJECT_NAME}
  ${TCL_LIBRARY}
  ${QT_LIBRARIES}
  ${PYTHON_LIBRARIES}
  dtkCore)

if(EDITLINE_FOUND)
  target_link_libraries(${PROJECT_NAME} ${EDITLINE_LIBRARY})
endif(EDITLINE_FOUND)

## #################################################################
## Installation
## #################################################################

install(FILES ${${PROJECT_NAME}_HEADERS} DESTINATION include/${PROJECT_NAME})
install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)

