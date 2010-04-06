### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Tue Mar 16 14:48:33 2010 (+0100)
## Version: $Id$
## Last-Updated: Tue Apr  6 09:19:54 2010 (+0200)
##           By: Julien Wintz
##     Update #: 9
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

project(dtkDistributedDiscovery)

## #################################################################
## Build rules
## #################################################################

add_executable(${PROJECT_NAME}
  main.cpp)

target_link_libraries(${PROJECT_NAME}
  ${QT_LIBRARIES}
  dtkCore
  dtkDistributed)
