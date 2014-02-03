### CMakeLists.txt --- 
## 
## Author: Thibaud Kloczko
## Copyright (C) 2011 - Thibaud Kloczko, Inria.
## Created: Mon Sep 26 09:27:41 2011 (+0200)
## Version: $Id$
## Last-Updated: Mon Jul 16 09:57:10 2012 (+0200)
##           By: tkloczko
##     Update #: 29
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

project(dtkContainerExample)

## #################################################################
## Build rules
## #################################################################

## set(${PROJECT_NAME}_SOURCE_MOC main.moc)

## qt4_generate_moc(main.cpp ${CMAKE_CURRENT_BINARY_DIR}/main.moc)

add_executable(${PROJECT_NAME} MACOSX_BUNDLE
  main.cpp
  ) ##${${PROJECT_NAME}_SOURCE_MOC})

target_link_libraries(${PROJECT_NAME}
  ${QT_LIBRARIES}
  dtkCore
  dtkContainer
  dtkComposer
  dtkGui
  dtkLog)
