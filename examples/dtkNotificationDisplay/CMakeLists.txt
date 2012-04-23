### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008-2011 - Julien Wintz, Inria.
## Created: Fri Apr 20 21:17:17 2012 (+0200)
## Version: $Id$
## Last-Updated: Mon Apr 23 22:18:42 2012 (+0200)
##           By: Julien Wintz
##     Update #: 17
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

project(dtkNotificationDisplay)

## #################################################################
## Build rules
## #################################################################

set(${PROJECT_NAME}_SOURCES     main.cpp)
set(${PROJECT_NAME}_SOURCES_MOC main.moc)

qt4_generate_moc(main.cpp ${CMAKE_CURRENT_BINARY_DIR}/main.moc)

add_executable(${PROJECT_NAME} MACOSX_BUNDLE
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_SOURCES_MOC})

target_link_libraries(${PROJECT_NAME}
  ${QT_LIBRARIES}
  dtkNotification)
