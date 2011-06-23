### CMakeLists.txt --- 
## 
## Author: Thibaud Kloczko
## Copyright (C) 2011 - Thibaud Kloczko, Inria.
## Created: Wed Mar  9 14:15:33 2011 (+0100)
## Version: $Id$
## Last-Updated: Mon Jun 20 18:17:22 2011 (+0200)
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

project(dtkCompareFloat)

## #################################################################
## Build rules
## #################################################################

add_executable(${PROJECT_NAME}
  main.cpp)

target_link_libraries(${PROJECT_NAME}
  dtkMath)
