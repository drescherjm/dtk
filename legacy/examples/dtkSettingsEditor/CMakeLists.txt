### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Wed Dec 23 10:00:14 2009 (+0100)
## Version: $Id$
## Last-Updated: Fri Apr 27 21:36:01 2012 (+0200)
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

project(dtkSettingsEditor)

## #################################################################
## Build rules
## #################################################################

add_executable(${PROJECT_NAME} MACOSX_BUNDLE
  main.cpp)

target_link_libraries(${PROJECT_NAME}
  ${QT_LIBRARIES}
  dtkCore
  dtkGui)

install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin
   BUNDLE DESTINATION bin)
