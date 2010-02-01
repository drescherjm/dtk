### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Mon Jul 20 18:39:20 2009 (+0200)
## Version: $Id$
## Last-Updated: Mon Feb  1 22:08:33 2010 (+0100)
##           By: Julien Wintz
##     Update #: 128
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

project(dtkCore)

## #################################################################
## Sources
## #################################################################

set(${PROJECT_NAME}_HEADERS
  dtkAbstractData.h
  dtkAbstractDataCell.h
  dtkAbstractDataEdge.h
  dtkAbstractDataFace.h
  dtkAbstractDataFactory.h
  dtkAbstractDataImage.h
  dtkAbstractDataImage2D.h
  dtkAbstractDataImage3D.h
  dtkAbstractDataMesh.h
  dtkAbstractDataMeshSurfacic.h
  dtkAbstractDataMeshVolumic.h
  dtkAbstractDataReader.h
  dtkAbstractDataVertex.h
  dtkAbstractDataWriter.h
  dtkAbstractFactory.h
  dtkAbstractObject.h
  dtkPlugin.h
  dtkAbstractProcess.h
  dtkAbstractProcessFactory.h
  dtkAbstractView.h
  dtkAbstractViewAnimator.h
  dtkAbstractViewFactory.h
  dtkAbstractViewInteractor.h
  dtkAbstractViewNavigator.h
  dtkCoreExport.h
  dtkGlobal.h
  dtkLog.h
  dtkPluginManager.h
  dtkUpdater.h
)

set(${PROJECT_NAME}_HEADERS_MOC
  dtkAbstractData.h
  dtkAbstractDataCell.h
  dtkAbstractDataEdge.h
  dtkAbstractDataFace.h
  dtkAbstractDataFactory.h
  dtkAbstractDataImage.h
  dtkAbstractDataImage2D.h
  dtkAbstractDataImage3D.h
  dtkAbstractDataMesh.h
  dtkAbstractDataMeshSurfacic.h
  dtkAbstractDataMeshVolumic.h
  dtkAbstractDataReader.h
  dtkAbstractDataVertex.h
  dtkAbstractDataWriter.h
  dtkAbstractFactory.h
  dtkAbstractObject.h
  dtkPlugin.h
  dtkAbstractProcess.h
  dtkAbstractProcessFactory.h
  dtkAbstractView.h
  dtkAbstractViewAnimator.h
  dtkAbstractViewFactory.h
  dtkAbstractViewInteractor.h
  dtkAbstractViewNavigator.h
  dtkPluginManager.h
  dtkUpdater_p.h
)

set(${PROJECT_NAME}_SOURCES
  dtkAbstractDataFactory.cpp
  dtkAbstractData.cpp
  dtkAbstractDataCell.cpp
  dtkAbstractDataEdge.cpp
  dtkAbstractDataFace.cpp
  dtkAbstractDataReader.cpp
  dtkAbstractDataWriter.cpp
  dtkAbstractDataImage.cpp
  dtkAbstractDataImage2D.cpp
  dtkAbstractDataImage3D.cpp
  dtkAbstractDataMesh.cpp
  dtkAbstractDataMeshSurfacic.cpp
  dtkAbstractDataMeshVolumic.cpp
  dtkAbstractDataVertex.cpp
  dtkAbstractFactory.cpp
  dtkAbstractObject.cpp
  dtkAbstractProcessFactory.cpp
  dtkAbstractProcess.cpp
  dtkAbstractViewFactory.cpp
  dtkAbstractView.cpp
  dtkAbstractViewAnimator.cpp
  dtkAbstractViewInteractor.cpp
  dtkAbstractViewNavigator.cpp
  dtkPlugin.cpp
  dtkLog.cpp
  dtkPluginManager.cpp
  dtkUpdater.cpp
)

## #################################################################
## Wrapping
## #################################################################

set(${PROJECT_NAME}_WRAP_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/dtkAbstractObject.h
  ${CMAKE_CURRENT_SOURCE_DIR}/dtkAbstractData.h
  ${CMAKE_CURRENT_SOURCE_DIR}/dtkAbstractDataFactory.h
  ${CMAKE_CURRENT_SOURCE_DIR}/dtkAbstractDataReader.h
  ${CMAKE_CURRENT_SOURCE_DIR}/dtkAbstractDataWriter.h
  ${CMAKE_CURRENT_SOURCE_DIR}/dtkAbstractProcess.h
  ${CMAKE_CURRENT_SOURCE_DIR}/dtkAbstractProcessFactory.h
  ${CMAKE_CURRENT_SOURCE_DIR}/dtkAbstractView.h
  ${CMAKE_CURRENT_SOURCE_DIR}/dtkAbstractViewFactory.h
  ${CMAKE_CURRENT_SOURCE_DIR}/dtkAbstractViewAnimator.h
  ${CMAKE_CURRENT_SOURCE_DIR}/dtkAbstractViewNavigator.h
  ${CMAKE_CURRENT_SOURCE_DIR}/dtkAbstractViewInteractor.h
  ${CMAKE_CURRENT_SOURCE_DIR}/dtkPlugin.h
  ${CMAKE_CURRENT_SOURCE_DIR}/dtkPluginManager.h)

dtk_wrap(${PROJECT_NAME} ${PROJECT_NAME}_SOURCES_WRAP core python ${CMAKE_CURRENT_SOURCE_DIR}/dtkCore.i ${${PROJECT_NAME}_WRAP_DEPENDS})
dtk_wrap(${PROJECT_NAME} ${PROJECT_NAME}_SOURCES_WRAP core tcl    ${CMAKE_CURRENT_SOURCE_DIR}/dtkCore.i ${${PROJECT_NAME}_WRAP_DEPENDS})

## #################################################################
## Build rules
## #################################################################

add_definitions(-Wno-write-strings)
add_definitions(-Wformat=0)

add_definitions(${QT_DEFINITIONS})
add_definitions(-DQT_SHARED)
add_definitions(-DQT_NO_DEBUG)

qt4_wrap_cpp(${PROJECT_NAME}_SOURCES_MOC ${${PROJECT_NAME}_HEADERS_MOC})

add_library(${PROJECT_NAME} SHARED
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_SOURCES_MOC}
  ${${PROJECT_NAME}_SOURCES_WRAP}
)

target_link_libraries(${PROJECT_NAME}
  ${QT_LIBRARIES}
  ${TCL_LIBRARY}
)

if(PYTHON_DEBUG_LIBRARIES)
  target_link_libraries(${PROJECT_NAME} debug ${PYTHON_DEBUG_LIBRARIES})
  target_link_libraries(${PROJECT_NAME} optimized ${PYTHON_LIBRARIES})
else(PYTHON_DEBUG_LIBRARIES)
  target_link_libraries(${PROJECT_NAME} ${PYTHON_LIBRARIES})
endif(PYTHON_DEBUG_LIBRARIES)

## #################################################################
## Handling of generated script modules
## #################################################################

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/dtkCore.i
  COMMAND ${CMAKE_COMMAND} ARGS -E  make_directory ${CMAKE_BINARY_DIR}/modules
  COMMAND ${CMAKE_COMMAND} ARGS -E  copy ${${PROJECT_NAME}_BINARY_DIR}/core.py ${CMAKE_BINARY_DIR}/modules
  COMMENT "-- Moving python modules to ${CMAKE_BINARY_DIR}/modules"
)

## #################################################################
## Installation
## #################################################################

if(NOT dtk_INSTALL_NO_DEVELOPMENT)
  install_files(${dtk_INSTALL_INCLUDE_DIR}/${PROJECT_NAME} .h ${${PROJECT_NAME}_HEADERS})
endif(NOT dtk_INSTALL_NO_DEVELOPMENT)

if(NOT dtk_INSTALL_NO_LIBRARIES)
  install_targets(${dtk_INSTALL_LIB_DIR} RUNTIME_DIRECTORY ${dtk_INSTALL_BIN_DIR} ${PROJECT_NAME})
  install_files(${dtk_INSTALL_MODULE_DIR} .py ${CMAKE_BINARY_DIR}/modules/core.py)
endif(NOT dtk_INSTALL_NO_LIBRARIES)
