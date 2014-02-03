### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Thu Oct 21 19:22:09 2010 (+0200)
## Version: $Id$
## Last-Updated: Thu Oct 21 19:24:06 2010 (+0200)
##           By: Julien Wintz
##     Update #: 8
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

project(dtkVrGestureRecognizer)

## #################################################################
## Build rules
## #################################################################

if(QUAT_LIBRARIES AND VRPN_LIBRARIES AND USE_MPI AND MPI_FOUND)

set(${PROJECT_NAME}_HEADERS_MOC
  tstMainWindow.h
  tstWidget.h)

set(${PROJECT_NAME}_SOURCES
  tstMainWindow.cpp
  tstWidget.cpp
  main.cpp)

## #################################################################
## Build rules
## #################################################################

qt4_wrap_cpp(${PROJECT_NAME}_SOURCES_MOC ${${PROJECT_NAME}_HEADERS_MOC})

add_executable(${PROJECT_NAME}
  ${${PROJECT_NAME}_SOURCES_MOC}
  ${${PROJECT_NAME}_SOURCES})

target_link_libraries(${PROJECT_NAME}
  ${QT_LIBRARIES}
  dtkVr)

endif(QUAT_LIBRARIES AND VRPN_LIBRARIES AND USE_MPI AND MPI_FOUND)
