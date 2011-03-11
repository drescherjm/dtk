### CMakeLists.txt --- 
## 
## Author: Thibaud Kloczko
## Copyright (C) 2011 - Thibaud Kloczko, Inria.
## Created: Wed Mar  9 14:15:50 2011 (+0100)
## Version: $Id$
## Last-Updated: Wed Mar  9 14:15:54 2011 (+0100)
##           By: Thibaud Kloczko
##     Update #: 1
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

project(dtkCompareDouble)

## #################################################################
## Build rules
## #################################################################

add_executable(${PROJECT_NAME} MACOSX_BUNDLE
  main.cpp)

target_link_libraries(${PROJECT_NAME}
  dtkMath)
