### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Wed Dec 23 10:00:14 2009 (+0100)
## Version: $Id$
## Last-Updated: Wed Dec 23 10:00:21 2009 (+0100)
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

project(dtkSettingsEditor)

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
