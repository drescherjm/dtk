### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Wed Jan 13 13:57:41 2010 (+0100)
## Version: $Id$
## Last-Updated: Thu Feb 25 20:31:35 2010 (+0100)
##           By: Julien Wintz
##     Update #: 175
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

project(dtkVr)

## #################################################################
## Resolve dependencies
## #################################################################

find_package(MPI)

if(MPI_FOUND)

## #################################################################
## Sources
## #################################################################

set(${PROJECT_NAME}_HEADERS
  dtkVrDevice.h
  dtkVrExport.h
  dtkVrScreen.h
  dtkVrManager.h
  dtkVrMaster.h
  dtkVrProcess.h
  dtkVrSlave.h
  dtkVrTracker.h
  dtkVrUser.h
  dtkVrWand.h
)

set(${PROJECT_NAME}_HEADERS_MOC
  dtkVrDevice.h
  dtkVrManager.h
  dtkVrTracker.h
  dtkVrUser.h
  dtkVrWand.h
)

set(${PROJECT_NAME}_SOURCES
  dtkVrDevice.cpp
  dtkVrScreen.cpp
  dtkVrManager.cpp
  dtkVrMaster.cpp
  dtkVrProcess.cpp
  dtkVrSlave.cpp
  dtkVrTracker.cpp
  dtkVrUser.cpp
  dtkVrWand.cpp
)

## #################################################################
## Vrpn sources
## #################################################################

if(QUAT_LIBRARIES AND VRPN_LIBRARIES)

set(${PROJECT_NAME}_HEADERS ${${PROJECT_NAME}_HEADERS}
  dtkVrDeviceVrpn.h
  dtkVrTrackerVrpn.h
)

set(${PROJECT_NAME}_HEADERS_MOC ${${PROJECT_NAME}_HEADERS_MOC}
  dtkVrDeviceVrpn.h
  dtkVrTrackerVrpn.h
)

set(${PROJECT_NAME}_SOURCES ${${PROJECT_NAME}_SOURCES}
  dtkVrDeviceVrpn.cpp
  dtkVrTrackerVrpn.cpp
)

endif(QUAT_LIBRARIES AND VRPN_LIBRARIES)

## #################################################################
## Wrapping
## #################################################################

set(${PROJECT_NAME}_WRAP_DEPENDS
  dtkVrProcess.h
)

dtk_wrap(${PROJECT_NAME} ${PROJECT_NAME}_SOURCES_WRAP vr python ${CMAKE_CURRENT_SOURCE_DIR}/dtkVr.i ${${PROJECT_NAME}_WRAP_DEPENDS})
dtk_wrap(${PROJECT_NAME} ${PROJECT_NAME}_SOURCES_WRAP vr tcl    ${CMAKE_CURRENT_SOURCE_DIR}/dtkVr.i ${${PROJECT_NAME}_WRAP_DEPENDS})

## #################################################################
## Build rules
## #################################################################

if(NOT WIN32)
add_definitions(-Wno-write-strings)
add_definitions(-Wformat=0)
endif(NOT WIN32)

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
  dtkCore
  dtkDistributed
)

if(MPI_FOUND)
target_link_libraries(${PROJECT_NAME}
  ${MPI_LIBRARIES}
)
endif(MPI_FOUND)

if(QUAT_LIBRARIES AND VRPN_LIBRARIES)
target_link_libraries(${PROJECT_NAME}
  ${QUAT_LIBRARIES}
  ${VRPN_LIBRARIES}
)
endif(QUAT_LIBRARIES AND VRPN_LIBRARIES)

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
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/dtkVr.i
  COMMAND ${CMAKE_COMMAND} ARGS -E  make_directory ${CMAKE_BINARY_DIR}/modules
  COMMAND ${CMAKE_COMMAND} ARGS -E  copy ${${PROJECT_NAME}_BINARY_DIR}/vr.py ${CMAKE_BINARY_DIR}/modules
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
  install_files(${dtk_INSTALL_MODULE_DIR} .py ${CMAKE_BINARY_DIR}/modules/vr.py)
endif(NOT dtk_INSTALL_NO_LIBRARIES)

endif(MPI_FOUND)
