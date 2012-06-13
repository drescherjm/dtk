### CMakeLists.txt --- 
## 
## Author: John Stark
## Copyright (C) 2011 - Thibaud Kloczko, Inria.
## Created: Wed May 25 16:00:00 2011 (+0100)
## Version: $Id$
## Last-Updated: Tue Apr  3 16:53:39 2012 (+0200)
##           By: tkloczko
##     Update #: 4
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

project(dtkSmartPointer)

## #################################################################
## Build rules
## #################################################################

add_executable(${PROJECT_NAME}
  main.cpp)

target_link_libraries(${PROJECT_NAME}
  dtkCore
  dtkLog)
