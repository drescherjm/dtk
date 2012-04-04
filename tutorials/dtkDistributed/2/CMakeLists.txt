### CMakeLists.txt --- 
## 
## Author: 
## Copyright (C) 2008-2011 - Julien Wintz, Inria.
## Created: Thu Sep  8 10:31:43 2011 (+0200)
## Version: $Id$
## Last-Updated: Wed Apr  4 10:57:49 2012 (+0200)
##           By: tkloczko
##     Update #: 11
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

project(dtkDistributedTutorial2)

## #################################################################
## Sources
## #################################################################

set(${PROJECT_NAME}_HEADERS)

set(${PROJECT_NAME}_SOURCES
  main.cpp)

## #################################################################
## Build rules
## #################################################################

add_executable(${PROJECT_NAME}
  ${${PROJECT_NAME}_HEADERS}
  ${${PROJECT_NAME}_SOURCES})

target_link_libraries(${PROJECT_NAME}
  dtkDistributed
  dtkLog)
