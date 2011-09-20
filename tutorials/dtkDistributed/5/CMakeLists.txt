### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008-2011 - Julien Wintz, Inria.
## Created: Tue Sep 20 11:20:07 2011 (+0200)
## Version: $Id$
## Last-Updated: Tue Sep 20 16:15:27 2011 (+0200)
##           By: Julien Wintz
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

project(dtkDistributedTutorial5)

## #################################################################
## Sources
## #################################################################

set(${PROJECT_NAME}_HEADERS
  tstMainWindow.h)

set(${PROJECT_NAME}_HEADERS_MOC
  tstMainWindow.h)

set(${PROJECT_NAME}_SOURCES
  tstMainWindow.cpp)

## #################################################################
## Build rules
## #################################################################

qt4_wrap_cpp(${PROJECT_NAME}_SOURCES_MOC ${${PROJECT_NAME}_HEADERS_MOC})

add_executable(dtkDistributedTutorial5Controller
  ${${PROJECT_NAME}_HEADERS}
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_SOURCES_MOC}
  controller_main.cpp)

add_executable(dtkDistributedTutorial5Server
  server_main.cpp)

target_link_libraries(dtkDistributedTutorial5Controller
  dtkCore
  dtkGui
  dtkDistributed)

target_link_libraries(dtkDistributedTutorial5Server
  dtkCore
  dtkDistributed)
