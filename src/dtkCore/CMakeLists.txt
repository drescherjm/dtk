### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Mon Jul 20 18:39:20 2009 (+0200)
## Version: $Id$
## Last-Updated: Tue Apr  6 21:34:38 2010 (+0200)
##           By: Julien Wintz
##     Update #: 138
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
  dtkQuat.h
  dtkUpdater.h
  dtkVec3.h)

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
  dtkUpdater_p.h)

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
  dtkQuat.cpp
  dtkUpdater.cpp)

## #################################################################
## Wrapping
## #################################################################

set(${PROJECT_NAME}_WRAP_DEPENDS ${${PROJECT_NAME}_HEADERS})

dtk_wrap(${PROJECT_NAME} ${PROJECT_NAME}_SOURCES_WRAP core python ${CMAKE_CURRENT_SOURCE_DIR}/dtkCore.i ${${PROJECT_NAME}_WRAP_DEPENDS})
dtk_wrap(${PROJECT_NAME} ${PROJECT_NAME}_SOURCES_WRAP core tcl    ${CMAKE_CURRENT_SOURCE_DIR}/dtkCore.i ${${PROJECT_NAME}_WRAP_DEPENDS})

## #################################################################
## Build rules
## #################################################################

if(NOT MSVC)
add_definitions(-Wno-write-strings)
add_definitions(-Wformat=0)
endif(NOT MSVC)

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
  ${TCL_LIBRARY}
  ${PYTHON_LIBRARIES})

## #################################################################
## Handling of generated script modules
## #################################################################

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/dtkCore.i
  COMMAND ${CMAKE_COMMAND} ARGS -E  make_directory ${CMAKE_BINARY_DIR}/modules
  COMMAND ${CMAKE_COMMAND} ARGS -E  copy ${${PROJECT_NAME}_BINARY_DIR}/core.py ${CMAKE_BINARY_DIR}/modules
  COMMENT "-- Moving python modules to ${CMAKE_BINARY_DIR}/modules")

set(${PROJECT_NAME}_MODULES ${CMAKE_BINARY_DIR}/modules/core.py)

## #################################################################
## Installation
## #################################################################

install(FILES ${${PROJECT_NAME}_HEADERS} DESTINATION include/${PROJECT_NAME})
install(FILES ${${PROJECT_NAME}_MODULES} DESTINATION modules)
install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)
