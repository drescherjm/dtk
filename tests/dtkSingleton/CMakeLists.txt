### CMakeLists.txt --- 
## 
## Author: John Stark
## Copyright (C) 2011 - Thibaud Kloczko, Inria.
## Created: Wed May 25 16:00:00 2011 (+0100)
## Version: $Id$
## Last-Updated: Mon Jun 20 18:17:39 2011 (+0200)
##           By: Julien Wintz
##     Update #: 2
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

project(dtkSingleton)

## #################################################################
## Build rules
## #################################################################

add_executable(${PROJECT_NAME}
  dtkTestSingleton.h
  dtkTestSingleton.cpp
  main.cpp)

target_link_libraries(${PROJECT_NAME}
  dtkCore)
