### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Fri Sep  4 10:11:02 2009 (+0200)
## Version: $Id$
## Last-Updated: Sun Sep 13 18:16:48 2009 (+0200)
##           By: Julien Wintz
##     Update #: 26
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
  dtkComposerNodeProperty.h
  dtkComposerScene.h
  dtkComposerView.h
)

set(${PROJECT_NAME}_HEADERS_MOC
  dtkComposer.h
  dtkComposerEdge.h
  dtkComposerEvaluator.h
  dtkComposerNode.h
  dtkComposerNodeProperty.h
  dtkComposerScene.h
)

set(${PROJECT_NAME}_SOURCES
  dtkComposer.cpp
  dtkComposerEdge.cpp
  dtkComposerEvaluator.cpp
  dtkComposerNode.cpp
  dtkComposerNodeProperty.cpp
  dtkComposerScene.cpp
  dtkComposerView.cpp
)

## #################################################################
## Build rules
## #################################################################

qt4_wrap_cpp(${PROJECT_NAME}_SOURCES_MOC ${${PROJECT_NAME}_HEADERS_MOC})

add_library(${PROJECT_NAME}
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_SOURCES_MOC}
  ${${PROJECT_NAME}_SOURCES_WRAP}
)

target_link_libraries(${PROJECT_NAME}
  ${QT_LIBRARIES}
  dtkCore
  dtkScript
)

if(PYTHON_DEBUG_LIBRARIES)
  target_link_libraries(${PROJECT_NAME} debug ${PYTHON_DEBUG_LIBRARIES})
  target_link_libraries(${PROJECT_NAME} optimized ${PYTHON_LIBRARIES})
else(PYTHON_DEBUG_LIBRARIES)
  target_link_libraries(${PROJECT_NAME} ${PYTHON_LIBRARIES})
endif(PYTHON_DEBUG_LIBRARIES)

## #################################################################
## Installation
## #################################################################

if(NOT dtk_INSTALL_NO_DEVELOPMENT)
  install_files(${dtk_INSTALL_INCLUDE_DIR}/${PROJECT_NAME} .h ${${PROJECT_NAME}_HEADERS})
endif(NOT dtk_INSTALL_NO_DEVELOPMENT)

if(NOT dtk_INSTALL_NO_LIBRARIES)
  install_targets(${dtk_INSTALL_LIB_DIR} RUNTIME_DIRECTORY ${dtk_INSTALL_BIN_DIR} ${PROJECT_NAME})
endif(NOT dtk_INSTALL_NO_LIBRARIES)
