### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Mon Feb 15 09:10:57 2010 (+0100)
## Version: $Id$
## Last-Updated: Mon Feb 15 20:13:30 2010 (+0100)
##           By: Julien Wintz
##     Update #: 23
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
  dtkAbstractCommunicator.h
  dtkCommunicatorTcp.h
  dtkCommunicatorUdp.h
  dtkDistributedExport.h
)

set(${PROJECT_NAME}_HEADERS_MOC
  dtkAbstractCommunicator.h
  dtkCommunicatorTcp.h
  dtkCommunicatorUdp.h
)

set(${PROJECT_NAME}_SOURCES
  dtkAbstractCommunicator.cpp
  dtkCommunicatorTcp.cpp
  dtkCommunicatorUdp.cpp
)

## #################################################################
## Mpi sources
## #################################################################

if(MPI_FOUND)

set(${PROJECT_NAME}_HEADERS ${${PROJECT_NAME}_HEADERS}
  dtkCommunicatorMpi.h
)

set(${PROJECT_NAME}_HEADERS_MOC ${${PROJECT_NAME}_HEADERS_MOC}
  dtkCommunicatorMpi.h
)

set(${PROJECT_NAME}_SOURCES ${${PROJECT_NAME}_SOURCES}
  dtkCommunicatorMpi.cpp
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
