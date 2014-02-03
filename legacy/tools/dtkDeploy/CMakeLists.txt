### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Thu Feb 10 11:57:22 2011 (+0100)
## Version: $Id$
## Last-Updated: Fri Apr 27 21:32:54 2012 (+0200)
##           By: Julien Wintz
##     Update #: 10
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

project(dtkDeploy)

## #################################################################
## Sources
## #################################################################

set(${PROJECT_NAME}_SOURCES
  dtkDeploy.h)

set(${PROJECT_NAME}_SOURCES
  dtkDeploy.cpp
  main.cpp)

## #################################################################
## Build rules
## #################################################################

add_executable(${PROJECT_NAME}
  ${${PROJECT_NAME}_SOURCES})

target_link_libraries(${PROJECT_NAME}
  ${QT_LIBRARIES})

## #################################################################
## Source file layout in development environments like Visual Studio
## #################################################################

SOURCE_GROUP("Header Files" REGULAR_EXPRESSION .*\\.h\$)

## #################################################################
## Installation
## #################################################################

install(TARGETS ${PROJECT_NAME}
   BUNDLE DESTINATION bin
  RUNTIME DESTINATION bin)
