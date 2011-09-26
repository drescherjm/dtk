### CMakeLists.txt --- 
## 
## Author: Thibaud Kloczko
## Copyright (C) 2011 - Thibaud Kloczko, Inria.
## Created: Mon Sep 26 09:27:41 2011 (+0200)
## Version: $Id$
## Last-Updated: Mon Sep 26 15:17:39 2011 (+0200)
##           By: Thibaud Kloczko
##     Update #: 20
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

project(dtkAbstractDataComposite)

## #################################################################
## Build rules
## #################################################################

set(${PROJECT_NAME}_SOURCE_MOC main.moc)

qt4_generate_moc(main.cpp ${CMAKE_CURRENT_BINARY_DIR}/main.moc)

add_executable(${PROJECT_NAME} MACOSX_BUNDLE
  ${${PROJECT_NAME}_SOURCES_MOC}
  main.cpp)

target_link_libraries(${PROJECT_NAME}
  ${QT_LIBRARIES}
  dtkCore)
  
