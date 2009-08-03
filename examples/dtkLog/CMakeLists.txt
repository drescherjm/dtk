### CMakeLists.txt --- 
## 
## Author: Jean-Christophe Lombardo
## Copyright (C) 2009 - Jean-Christophe Lombardo, Inria
## Created: Fri May 15 13:46:51 2009
## Version: $Id$
## Last-Updated: Mon Jul 20 22:36:56 2009 (+0200)
##           By: Julien Wintz
##     Update #: 4
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
  main.cpp
)

target_link_libraries(${PROJECT_NAME}
  ${QT_LIBRARIES}
  dtkCore
  dtkGui
)

## -*- tab-width: 4; indent-tabs-mode: nil c-basic-offset: 4 -*-
## vim:cindent:ts=4:sw=4:et:tw=80:sta:
