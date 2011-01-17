### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008-2009 - Julien Wintz, Inria.
## Created: Tue Mar 10 15:12:38 2009 (+0100)
## Version: $Id$
## Last-Updated: Fri Oct 15 11:23:47 2010 (+0200)
##           By: Julien Wintz
##     Update #: 50
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
  dtkScriptManager.h)

set(${PROJECT_NAME}_HEADERS_MOC
  dtkScriptInterpreter.h
  dtkScriptInterpreterPool.h
  dtkScriptManager.h)

set(${PROJECT_NAME}_SOURCES
  dtkScriptInterpreter.cpp
  dtkScriptInterpreterPool.cpp
  dtkScriptManager.cpp)

if(BUILD_WRAPPERS)
set(${PROJECT_NAME}_HEADERS ${${PROJECT_NAME}_HEADERS}
  dtkScriptInterpreterPython.h
  dtkScriptInterpreterTcl.h)

set(${PROJECT_NAME}_HEADERS_MOC ${${PROJECT_NAME}_HEADERS_MOC}
  dtkScriptInterpreterPython.h
  dtkScriptInterpreterTcl.h)

set(${PROJECT_NAME}_SOURCES ${${PROJECT_NAME}_SOURCES}
  dtkScriptInterpreterPython.cpp
  dtkScriptInterpreterTcl.cpp)
endif(BUILD_WRAPPERS)

## #################################################################
## Build rules
## #################################################################

add_definitions(${QT_DEFINITIONS})
add_definitions(-DQT_SHARED)
if(NOT MSVC)
  add_definitions(-DQT_NO_DEBUG)
endif(NOT MSVC)

qt4_wrap_cpp(${PROJECT_NAME}_SOURCES_MOC ${${PROJECT_NAME}_HEADERS_MOC})

add_library(${PROJECT_NAME} SHARED
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_HEADERS}
  ${${PROJECT_NAME}_SOURCES_MOC})

target_link_libraries(${PROJECT_NAME}
  ${TCL_LIBRARY}
  dtkCore)

if(BUILD_WRAPPERS)
target_link_libraries(${PROJECT_NAME}
  ${TCL_LIBRARY}
  ${PYTHON_LIBRARIES})
endif(BUILD_WRAPPERS)

if(EDITLINE_FOUND)
  target_link_libraries(${PROJECT_NAME} ${EDITLINE_LIBRARY})
endif(EDITLINE_FOUND)

## #################################################################
## Source file layout in development environments like Visual Studio
## #################################################################

SOURCE_GROUP("Header Files" REGULAR_EXPRESSION .*\\.h\$)
SOURCE_GROUP("Generated Files" FILES ${${PROJECT_NAME}_SOURCES_UIC} ${${PROJECT_NAME}_SOURCES_MOC} ${${PROJECT_NAME}_SOURCES_QRC})

## #################################################################
## Installation
## #################################################################

install(FILES ${${PROJECT_NAME}_HEADERS} DESTINATION include/${PROJECT_NAME})
install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)

