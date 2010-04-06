### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Thu Dec 10 14:04:48 2009 (+0100)
## Version: $Id$
## Last-Updated: Tue Apr  6 09:08:53 2010 (+0200)
##           By: Julien Wintz
##     Update #: 7
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

project(dtksh)

## #################################################################
## Sources
## #################################################################

set(${PROJECT_NAME}_SOURCES
  main.cpp)

## #################################################################
## Build rules
## #################################################################

add_executable(${PROJECT_NAME}
  ${${PROJECT_NAME}_SOURCES_UIC}
  ${${PROJECT_NAME}_SOURCES_MOC}
  ${${PROJECT_NAME}_SOURCES})

target_link_libraries(${PROJECT_NAME}
  ${QT_LIBRARIES}
  dtkCore
  dtkScript)

## #################################################################
## Installation
## #################################################################

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
