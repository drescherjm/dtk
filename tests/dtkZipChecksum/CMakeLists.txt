### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008-2011 - Julien Wintz, Inria.
## Created: Tue Jun 21 15:40:51 2011 (+0200)
## Version: $Id$
## Last-Updated: Tue Jun 21 15:41:09 2011 (+0200)
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

project(dtkZipChecksum)

## #################################################################
## Build rules
## #################################################################

add_executable(${PROJECT_NAME}
  main.cpp)

target_link_libraries(${PROJECT_NAME}
  dtkZip)
