### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Mon Jul 20 18:39:20 2009 (+0200)
## Version: $Id$
## Last-Updated: Sat Jun 25 15:49:02 2011 (+0200)
##           By: Julien Wintz
##     Update #: 194
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
  dtkAbstractDataFactory.h
  dtkAbstractDataReader.h
  dtkAbstractDataWriter.h
  dtkAbstractDataConverter.h
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
  dtkSignalBlocker.h
  dtkSmartPointer.h
  dtkVec3.h)

set(${PROJECT_NAME}_HEADERS_MOC
  dtkAbstractData.h
  dtkAbstractDataFactory.h
  dtkAbstractDataReader.h
  dtkAbstractDataWriter.h
  dtkAbstractDataConverter.h
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
  dtkAbstractDataReader.cpp
  dtkAbstractDataWriter.cpp
  dtkAbstractDataConverter.cpp
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
  dtkSignalBlocker.h
  dtkSmartPointer.cpp
  dtkUpdater.cpp)

## #################################################################
## Wrapping
## #################################################################

set(${PROJECT_NAME}_SOURCES_WRAP)

if(BUILD_WRAPPERS AND SWIG_FOUND)

  set(${PROJECT_NAME}_WRAP_DEPENDS ${${PROJECT_NAME}_HEADERS})
  
  if(PYTHONLIBS_FOUND)
    dtk_wrap(${PROJECT_NAME} ${PROJECT_NAME}_SOURCES_WRAP core python ${PROJECT_SOURCE_DIR}/dtkCore.i ${${PROJECT_NAME}_WRAP_DEPENDS})
  endif()
  
  if(TCL_FOUND)
    dtk_wrap(${PROJECT_NAME} ${PROJECT_NAME}_SOURCES_WRAP core tcl    ${PROJECT_SOURCE_DIR}/dtkCore.i ${${PROJECT_NAME}_WRAP_DEPENDS})
  endif()
  
endif()

## #################################################################
## Configure file
## #################################################################

configure_file (
  "${PROJECT_SOURCE_DIR}/dtkConfig.h.in"
  "${PROJECT_BINARY_DIR}/../../dtkConfig.h")

## #################################################################
## Build rules
## #################################################################

if(NOT MSVC)
add_definitions(-Wno-write-strings)
add_definitions(-Wformat=0)
endif()

add_definitions(${QT_DEFINITIONS})
add_definitions(-DQT_SHARED)
if(NOT MSVC)
  # Shouldn't the QT_USE_FILE set this appropriately?
  add_definitions(-DQT_NO_DEBUG)
endif()

qt4_wrap_cpp(${PROJECT_NAME}_SOURCES_MOC ${${PROJECT_NAME}_HEADERS_MOC})

add_library(${PROJECT_NAME} SHARED
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_HEADERS}
  ${${PROJECT_NAME}_SOURCES_MOC}
  ${${PROJECT_NAME}_SOURCES_WRAP})

target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES})

if(TCL_FOUND)
  target_link_libraries(${PROJECT_NAME} ${TCL_LIBRARY})
endif()

if(PYTHONLIBS_FOUND)
  target_link_libraries(${PROJECT_NAME} ${PYTHON_LIBRARIES})
endif()

## #################################################################
## Handling of generated script modules
## #################################################################

set(${PROJECT_NAME}_MODULES)

if(BUILD_WRAPPERS AND SWIG_FOUND AND PYTHONLIBS_FOUND)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  DEPENDS ${PROJECT_SOURCE_DIR}/dtkCore.i
  COMMAND ${CMAKE_COMMAND} ARGS -E  make_directory ${PROJECT_BINARY_DIR}/modules
  COMMAND ${CMAKE_COMMAND} ARGS -E  copy ${${PROJECT_NAME}_BINARY_DIR}/core.py ${PROJECT_BINARY_DIR}/modules
  COMMENT "-- Moving python modules to ${CMAKE_BINARY_DIR}/modules")

set(${PROJECT_NAME}_MODULES ${CMAKE_BINARY_DIR}/modules/core.py)

endif()

## #################################################################
## Source file layout in development environments like Visual Studio
## #################################################################

SOURCE_GROUP("Header Files" REGULAR_EXPRESSION .*\\.h\$)
SOURCE_GROUP("Generated Files" FILES ${${PROJECT_NAME}_SOURCES_MOC})

## #################################################################
## Installation
## #################################################################

install(FILES ${${PROJECT_NAME}_HEADERS} DESTINATION include/${PROJECT_NAME})
install(FILES ${${PROJECT_NAME}_MODULES} DESTINATION modules)
install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)

