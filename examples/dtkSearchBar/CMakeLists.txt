### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Wed Dec  9 09:19:02 2009 (+0100)
## Version: $Id$
## Last-Updated: Wed Dec  9 09:19:17 2009 (+0100)
##           By: Julien Wintz
##     Update #: 2
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

project(dtkSearchBar)

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
