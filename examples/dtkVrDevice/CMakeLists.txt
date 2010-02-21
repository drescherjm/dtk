### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Sun Feb 21 17:05:22 2010 (+0100)
## Version: $Id$
## Last-Updated: Sun Feb 21 17:05:31 2010 (+0100)
##           By: Julien Wintz
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

project(dtkVrDevice)

## #################################################################
## Build rules
## #################################################################

add_executable(${PROJECT_NAME}
  main.cpp
)

target_link_libraries(${PROJECT_NAME}
  ${QT_LIBRARIES}
  dtkVr
)
