### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008-2011 - Julien Wintz, Inria.
## Created: Mon Sep 12 09:57:47 2011 (+0200)
## Version: $Id$
## Last-Updated: Mon Sep 12 09:57:58 2011 (+0200)
##           By: Julien Wintz
##     Update #: 3
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

project(dtkDistributedTutorial3)

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
  dtkCore
  dtkDistributed)
