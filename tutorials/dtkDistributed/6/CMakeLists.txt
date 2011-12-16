### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008-2011 - Julien Wintz, Inria.
## Created: Wed Sep 14 13:17:50 2011 (+0200)
## Version: $Id$
## Last-Updated: mar. déc.  6 10:52:11 2011 (+0100)
##           By: Nicolas Niclausse
##     Update #: 25
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

project(dtkDistributedTutorial6)

## #################################################################
## Sources
## #################################################################

set(${PROJECT_NAME}_HEADERS
  tstMainWindow.h
)

set(${PROJECT_NAME}_HEADERS_MOC
  tstMainWindow.h)

set(${PROJECT_NAME}_SOURCES
  tstMainWindow.cpp )

## #################################################################
## Build rules
## #################################################################
qt4_wrap_cpp(${PROJECT_NAME}_SOURCES_MOC ${${PROJECT_NAME}_HEADERS_MOC})

add_executable(dtkDistributedTutorial6Slave
  dtkDistributedTutorial6Slave.h
  dtkDistributedTutorial6Slave.cpp
  slave_main.cpp)

add_executable(dtkDistributedTutorial6Controller
  ${${PROJECT_NAME}_HEADERS}
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_SOURCES_MOC}
  controller_main.cpp)


target_link_libraries(dtkDistributedTutorial6Slave
  dtkCore
  dtkDistributed)

target_link_libraries(dtkDistributedTutorial6Controller
  dtkCore
  dtkGui
  dtkDistributed)
