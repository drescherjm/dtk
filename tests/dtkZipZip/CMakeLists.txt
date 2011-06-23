### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008-2011 - Julien Wintz, Inria.
## Created: Tue Jun 21 15:29:32 2011 (+0200)
## Version: $Id$
## Last-Updated: Tue Jun 21 15:31:21 2011 (+0200)
##           By: Julien Wintz
##     Update #: 6
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

project(dtkZipZip)

## #################################################################
## Build rules
## #################################################################

add_executable(${PROJECT_NAME}
  main.cpp)

target_link_libraries(${PROJECT_NAME}
  dtkZip)
