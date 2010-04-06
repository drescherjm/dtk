### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Sun Feb 21 17:05:22 2010 (+0100)
## Version: $Id$
## Last-Updated: Tue Apr  6 09:19:43 2010 (+0200)
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

project(dtkVrDevice)

## #################################################################
## Build rules
## #################################################################

if(QUAT_LIBRARIES AND VRPN_LIBRARIES)

add_executable(${PROJECT_NAME}
  main.cpp)

target_link_libraries(${PROJECT_NAME}
  ${QT_LIBRARIES}
  dtkVr)

endif(QUAT_LIBRARIES AND VRPN_LIBRARIES)
