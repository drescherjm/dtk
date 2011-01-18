### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Sun Feb 21 17:05:22 2010 (+0100)
## Version: $Id$
## Last-Updated: Tue Jan 18 18:06:13 2011 (+0100)
##           By: Julien Wintz
##     Update #: 7
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

if(QUAT_LIBRARIES AND VRPN_LIBRARIES AND MPI_FOUND)

add_executable(${PROJECT_NAME}
  main.cpp)

target_link_libraries(${PROJECT_NAME}
  ${QT_LIBRARIES}
  dtkVr)

endif(QUAT_LIBRARIES AND VRPN_LIBRARIES AND MPI_FOUND)
