### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008-2011 - Julien Wintz, Inria.
## Created: Thu Mar  1 14:34:49 2012 (+0100)
## Version: $Id$
## Last-Updated: Mon Apr 16 12:02:24 2012 (+0200)
##           By: Julien Wintz
##     Update #: 29
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

project(dtkLog)

## #################################################################
## Sources
## #################################################################

set(${PROJECT_NAME}_HEADERS
  dtkLog.h
  dtkLogger.h
  dtkLogEngine.h
  dtkLogDestination.h
  dtkLogModel.h
  dtkLogView.h)

set(${PROJECT_NAME}_HEADERS_MOC
  dtkLogModel.h
  dtkLogView.h
  dtkLogView_p.h)

set(${PROJECT_NAME}_SOURCES
  dtkLog.cpp
  dtkLogger.cpp
  dtkLogEngine.cpp
  dtkLogDestination.cpp
  dtkLogModel.cpp
  dtkLogView.cpp)

## #################################################################
## Build rules
## #################################################################

if(NOT WIN32)
add_definitions(-Wno-write-strings)
endif(NOT WIN32)

add_definitions(${QT_DEFINITIONS})
add_definitions(-DQT_SHARED)

if(NOT WIN32)
  add_definitions(-DQT_NO_DEBUG)
endif(NOT WIN32)

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
  ${QT_LIBRARIES})

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
SOURCE_GROUP("Generated Files" FILES ${${PROJECT_NAME}_SOURCES_MOC})

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
