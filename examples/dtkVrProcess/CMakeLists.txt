### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Fri Feb 12 21:00:35 2010 (+0100)
## Version: $Id$
## Last-Updated: Tue Apr  6 09:19:31 2010 (+0200)
##           By: Julien Wintz
##     Update #: 10
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

project(dtkVrProcess)

## #################################################################
## Build rules
## #################################################################

if(QUAT_LIBRARIES AND VRPN_LIBRARIES AND USE_MPI AND MPI_FOUND)

add_executable(${PROJECT_NAME}
  main.cpp)

target_link_libraries(${PROJECT_NAME}
  ${QT_LIBRARIES}
  dtkVr)

endif(QUAT_LIBRARIES AND VRPN_LIBRARIES AND USE_MPI AND MPI_FOUND)
