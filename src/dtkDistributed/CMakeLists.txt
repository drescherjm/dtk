### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Mon Feb 15 09:10:57 2010 (+0100)
## Version: $Id$
## Last-Updated: Thu Feb 18 14:14:42 2010 (+0100)
##           By: Julien Wintz
##     Update #: 33
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

project(dtkDistributed)

## #################################################################
## Sources
## #################################################################

set(${PROJECT_NAME}_HEADERS
  dtkDistributedCommunicator.h
  dtkDistributedCommunicatorTcp.h
  dtkDistributedCore.h
  dtkDistributedDiscoverer.h
  dtkDistributedCpu.h
  dtkDistributedGpu.h
  dtkDistributedNode.h
  dtkDistributedExport.h
)

set(${PROJECT_NAME}_HEADERS_MOC
  dtkDistributedCommunicator.h
  dtkDistributedCommunicatorTcp.h
  dtkDistributedCore.h
  dtkDistributedDiscoverer.h
  dtkDistributedCpu.h
  dtkDistributedGpu.h
  dtkDistributedNode.h
)

set(${PROJECT_NAME}_SOURCES
  dtkDistributedCommunicator.cpp
  dtkDistributedCommunicatorTcp.cpp
  dtkDistributedCore.cpp
  dtkDistributedDiscoverer.cpp
  dtkDistributedCpu.cpp
  dtkDistributedGpu.cpp
  dtkDistributedNode.cpp
)

## #################################################################
## Mpi sources
## #################################################################

if(MPI_FOUND)

set(${PROJECT_NAME}_HEADERS ${${PROJECT_NAME}_HEADERS}
  dtkDistributedCommunicatorMpi.h
)

set(${PROJECT_NAME}_HEADERS_MOC ${${PROJECT_NAME}_HEADERS_MOC}
  dtkDistributedCommunicatorMpi.h
)

set(${PROJECT_NAME}_SOURCES ${${PROJECT_NAME}_SOURCES}
  dtkDistributedCommunicatorMpi.cpp
)

endif(MPI_FOUND)

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
)

target_link_libraries(${PROJECT_NAME}
  ${QT_LIBRARIES}
  dtkCore
)

if(MPI_FOUND)

target_link_libraries(${PROJECT_NAME}
  ${MPI_LIBRARIES}
)

endif(MPI_FOUND)

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
