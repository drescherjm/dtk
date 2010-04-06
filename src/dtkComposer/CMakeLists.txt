### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Fri Sep  4 10:11:02 2009 (+0200)
## Version: $Id$
## Last-Updated: Tue Apr  6 09:42:11 2010 (+0200)
##           By: Julien Wintz
##     Update #: 39
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

project(dtkComposer)

## #################################################################
## Sources
## #################################################################

set(${PROJECT_NAME}_HEADERS
  dtkComposer.h
  dtkComposerEdge.h
  dtkComposerEvaluator.h
  dtkComposerExport.h
  dtkComposerNode.h
  dtkComposerNodeFactory.h
  dtkComposerNodeProperty.h
  dtkComposerScene.h
  dtkComposerView.h)

set(${PROJECT_NAME}_HEADERS_MOC
  dtkComposer.h
  dtkComposerEdge.h
  dtkComposerEvaluator.h
  dtkComposerNode.h
  dtkComposerNodeFactory.h
  dtkComposerNodeProperty.h
  dtkComposerScene.h
  dtkComposerView.h)

set(${PROJECT_NAME}_SOURCES
  dtkComposer.cpp
  dtkComposerEdge.cpp
  dtkComposerEvaluator.cpp
  dtkComposerNode.cpp
  dtkComposerNodeFactory.cpp
  dtkComposerNodeProperty.cpp
  dtkComposerScene.cpp
  dtkComposerView.cpp)

## #################################################################
## Build rules
## #################################################################

add_definitions(${QT_DEFINITIONS})
add_definitions(-DQT_SHARED)
add_definitions(-DQT_NO_DEBUG)

qt4_wrap_cpp(${PROJECT_NAME}_SOURCES_MOC ${${PROJECT_NAME}_HEADERS_MOC})

add_library(${PROJECT_NAME} SHARED
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_SOURCES_MOC}
  ${${PROJECT_NAME}_SOURCES_WRAP})

target_link_libraries(${PROJECT_NAME}
  ${QT_LIBRARIES}
  dtkCore
  dtkScript)

## #################################################################
## Installation
## #################################################################

install(FILES ${${PROJECT_NAME}_HEADERS} DESTINATION include/${PROJECT_NAME})
install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)
