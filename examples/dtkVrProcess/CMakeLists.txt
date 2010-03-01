### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Fri Feb 12 21:00:35 2010 (+0100)
## Version: $Id$
## Last-Updated: Mon Mar  1 12:41:19 2010 (+0100)
##           By: Julien Wintz
##     Update #: 9
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

if(QUAT_LIBRARIES AND VRPN_LIBRARIES AND MPI_FOUND)

add_executable(${PROJECT_NAME}
  main.cpp
)

target_link_libraries(${PROJECT_NAME}
  ${QT_LIBRARIES}
  dtkVr
)

endif(QUAT_LIBRARIES AND VRPN_LIBRARIES AND MPI_FOUND)

