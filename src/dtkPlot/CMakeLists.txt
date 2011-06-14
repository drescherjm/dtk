### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Mon Nov 22 10:20:27 2010 (+0100)
## Version: $Id$
## Last-Updated: Tue Jun  7 16:38:39 2011 (+0200)
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

if(QWT_FOUND)

## #################################################################
## 
## #################################################################

project(dtkPlot)

## #################################################################
## Sources
## #################################################################

set(${PROJECT_NAME}_HEADERS
  dtkPlotCurve.h
  dtkPlotExport.h
  dtkPlotView.h)

set(${PROJECT_NAME}_HEADERS_MOC
  dtkPlotView.h)

set(${PROJECT_NAME}_SOURCES
  dtkPlotCurve.cpp
  dtkPlotView.cpp)

## #################################################################
## Build rules
## #################################################################

if(NOT WIN32)
add_definitions(-Wno-write-strings)
add_definitions(-Wformat=0)
endif(NOT WIN32)

add_definitions(${QT_DEFINITIONS})
add_definitions(-DQT_SHARED)

if(NOT WIN32)
  add_definitions(-DQT_NO_DEBUG)
endif(NOT WIN32)

qt4_wrap_cpp(${PROJECT_NAME}_SOURCES_MOC ${${PROJECT_NAME}_HEADERS_MOC})

add_library(${PROJECT_NAME} SHARED
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_HEADERS}
  ${${PROJECT_NAME}_SOURCES_MOC})

target_link_libraries(${PROJECT_NAME}
  ${QT_LIBRARIES}
  ${QWT_LIBRARY})

## #################################################################
## Source file layout in development environments like Visual Studio
## #################################################################

SOURCE_GROUP("Header Files" REGULAR_EXPRESSION .*\\.h\$)
SOURCE_GROUP("Generated Files" FILES ${${PROJECT_NAME}_SOURCES_MOC})

## #################################################################
## Installation
## #################################################################

install(FILES ${${PROJECT_NAME}_HEADERS} DESTINATION include/${PROJECT_NAME})
install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)

## #################################################################
## 
## #################################################################

endif(QWT_FOUND)
