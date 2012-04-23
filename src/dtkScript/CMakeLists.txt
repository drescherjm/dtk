### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008-2009 - Julien Wintz, Inria.
## Created: Tue Mar 10 15:12:38 2009 (+0100)
## Version: $Id$
## Last-Updated: Mon Apr 16 12:03:01 2012 (+0200)
##           By: Julien Wintz
##     Update #: 63
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

if(DTK_BUILD_WRAPPERS)
set(${PROJECT_NAME}_HEADERS ${${PROJECT_NAME}_HEADERS}
  dtkScriptInterpreterPython.h
  dtkScriptInterpreterTcl.h)

set(${PROJECT_NAME}_HEADERS_MOC ${${PROJECT_NAME}_HEADERS_MOC}
  dtkScriptInterpreterPython.h
  dtkScriptInterpreterTcl.h)

set(${PROJECT_NAME}_SOURCES ${${PROJECT_NAME}_SOURCES}
  dtkScriptInterpreterPython.cpp
  dtkScriptInterpreterTcl.cpp)
endif(DTK_BUILD_WRAPPERS)

## #################################################################
## Build rules
## #################################################################

add_definitions(${QT_DEFINITIONS})
add_definitions(-DQT_SHARED)
if(NOT MSVC)
  add_definitions(-DQT_NO_DEBUG)
endif(NOT MSVC)

qt4_wrap_cpp(${PROJECT_NAME}_SOURCES_MOC ${${PROJECT_NAME}_HEADERS_MOC})

if(BUILD_SHARED_LIBS)

add_library(${PROJECT_NAME} SHARED
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_HEADERS}
  ${${PROJECT_NAME}_SOURCES_MOC})

else(BUILD_SHARED_LIBS)

add_library(${PROJECT_NAME} STATIC
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_HEADERS}
  ${${PROJECT_NAME}_SOURCES_MOC})

endif(BUILD_SHARED_LIBS)

target_link_libraries(${PROJECT_NAME}
  dtkCore
  dtkLog)

if(DTK_BUILD_WRAPPERS)
target_link_libraries(${PROJECT_NAME}
  ${TCL_LIBRARY}
  ${PYTHON_LIBRARIES})
endif(DTK_BUILD_WRAPPERS)

if(EDITLINE_FOUND)
  target_link_libraries(${PROJECT_NAME} ${EDITLINE_LIBRARY})
endif(EDITLINE_FOUND)

## #################################################################
## Export header file
## #################################################################

add_compiler_export_flags()

generate_export_header(${PROJECT_NAME}
  EXPORT_FILE_NAME "${PROJECT_NAME}Export.h")

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
  COMMAND ${CMAKE_COMMAND} ARGS -E copy
  "${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}Export.h"
  "${CMAKE_BINARY_DIR}")

## #################################################################
## Source file layout in development environments like Visual Studio
## #################################################################

SOURCE_GROUP("Header Files" REGULAR_EXPRESSION .*\\.h\$)
SOURCE_GROUP("Generated Files" FILES ${${PROJECT_NAME}_SOURCES_UIC} ${${PROJECT_NAME}_SOURCES_MOC} ${${PROJECT_NAME}_SOURCES_QRC})

## #################################################################
## Installation
## #################################################################

foreach(header ${${PROJECT_NAME}_HEADERS})
  string(REGEX REPLACE "(.*)\\.h\$" "\\1" h ${header})
  set(${PROJECT_NAME}_HEADERS_QTS "${${PROJECT_NAME}_HEADERS_QTS}" ${h})
endforeach(header)

set(${PROJECT_NAME}_HEADERS
  ${${PROJECT_NAME}_HEADERS}
 "${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}Export.h")

install(FILES ${${PROJECT_NAME}_HEADERS} DESTINATION include/${PROJECT_NAME})
install(FILES ${${PROJECT_NAME}_HEADERS_QTS} DESTINATION include/${PROJECT_NAME})
install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)

