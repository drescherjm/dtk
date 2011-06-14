### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008-2011 - Julien Wintz, Inria.
## Created: Tue Jun  7 15:26:12 2011 (+0200)
## Version: $Id$
## Last-Updated: Wed Jun  8 09:50:33 2011 (+0200)
##           By: Julien Wintz
##     Update #: 13
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

project(dtkPlotEcg)

## #################################################################
## Sources
## #################################################################

set(${PROJECT_NAME}_HEADERS_MOC
  tstMainWindow.h
  tstSidePane.h)

set(${PROJECT_NAME}_SOURCES
  tstPlotCurveEcg.cpp
  tstMainWindow.cpp
  tstSidePane.cpp
  main.cpp)

set(${PROJECT_NAME}_RESOURCES
  dtkPlotEcg.qrc)

## #################################################################
## Build rules
## #################################################################

qt4_wrap_cpp(${PROJECT_NAME}_SOURCES_MOC ${${PROJECT_NAME}_HEADERS_MOC})
qt4_add_RESOURCES(${PROJECT_NAME}_SOURCES_QRC ${${PROJECT_NAME}_RESOURCES})

add_executable(${PROJECT_NAME} MACOSX_BUNDLE
  ${${PROJECT_NAME}_SOURCES_MOC}
  ${${PROJECT_NAME}_SOURCES_QRC}
  ${${PROJECT_NAME}_SOURCES})

target_link_libraries(${PROJECT_NAME}
  ${QT_LIBRARIES}
  dtkGui
  dtkPlot)

## #################################################################
## 
## #################################################################

endif(QWT_FOUND)
