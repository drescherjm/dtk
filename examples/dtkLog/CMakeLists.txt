### CMakeLists.txt --- 
## 
## Author: Jean-Christophe Lombardo
## Copyright (C) 2009 - Jean-Christophe Lombardo, Inria
## Created: Fri May 15 13:46:51 2009
## Version: $Id$
## Last-Updated: Tue Apr  6 09:17:59 2010 (+0200)
##           By: Julien Wintz
##     Update #: 5
##
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

project(dtkLog)

## #################################################################
## Build rules
## #################################################################

add_executable(${PROJECT_NAME} MACOSX_BUNDLE
  main.cpp)

target_link_libraries(${PROJECT_NAME}
  ${QT_LIBRARIES}
  dtkCore
  dtkGui)
