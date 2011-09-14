### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008-2011 - Julien Wintz, Inria.
## Created: Wed Sep 14 13:17:50 2011 (+0200)
## Version: $Id$
## Last-Updated: Wed Sep 14 13:22:58 2011 (+0200)
##           By: Julien Wintz
##     Update #: 14
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

project(dtkDistributedTutorial4)

## #################################################################
## Sources
## #################################################################

set(${PROJECT_NAME}_HEADERS
  dtkDistributedTutorial4Slave.h)

set(${PROJECT_NAME}_SOURCES
  dtkDistributedTutorial4Slave.cpp)

## #################################################################
## Build rules
## #################################################################

add_executable(dtkDistributedTutorial4Slave
  ${${PROJECT_NAME}_HEADERS}
  ${${PROJECT_NAME}_SOURCES}
  slave_main.cpp)

add_executable(dtkDistributedTutorial4Server
  ${${PROJECT_NAME}_HEADERS}
  ${${PROJECT_NAME}_SOURCES}
  server_main.cpp)

target_link_libraries(dtkDistributedTutorial4Slave
  dtkCore
  dtkDistributed)

target_link_libraries(dtkDistributedTutorial4Server
  dtkCore
  dtkDistributed)
