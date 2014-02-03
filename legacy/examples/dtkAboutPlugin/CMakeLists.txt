### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008-2011 - Julien Wintz, Inria.
## Created: Mon Sep  5 13:18:52 2011 (+0200)
## Version: $Id$
## Last-Updated: Fri Apr 27 21:36:19 2012 (+0200)
##           By: Julien Wintz
##     Update #: 8
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

project(dtkAboutPlugin)

## #################################################################
## Sources
## #################################################################

set(${PROJECT_NAME}_HEADERS_MOC
  tstMainWindow.h)

set(${PROJECT_NAME}_SOURCES
  tstMainWindow.cpp
  main.cpp)

## #################################################################
## Build rules
## #################################################################

qt4_wrap_cpp(${PROJECT_NAME}_SOURCES_MOC ${${PROJECT_NAME}_HEADERS_MOC})

add_executable(${PROJECT_NAME} MACOSX_BUNDLE
  ${${PROJECT_NAME}_SOURCES_MOC}
  ${${PROJECT_NAME}_SOURCES})

target_link_libraries(${PROJECT_NAME}
  ${QT_LIBRARIES}
  dtkCore
  dtkGui)

install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin
   BUNDLE DESTINATION bin)
