### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Mon Feb 15 09:10:57 2010 (+0100)
## Version: $Id$
## Last-Updated: Tue Jun  8 11:34:56 2010 (+0200)
##           By: Julien Wintz
##     Update #: 67
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
  dtkDistributedDiscovererOar.h
  dtkDistributedDiscovererTorque.h
  dtkDistributedCpu.h
  dtkDistributedGpu.h
  dtkDistributedExport.h
  dtkDistributedNode.h
  dtkDistributor.h
  dtkDistributorController.h
  dtkDistributorScene.h
  dtkDistributorView.h)

set(${PROJECT_NAME}_HEADERS_MOC
  dtkDistributedCommunicator.h
  dtkDistributedCommunicatorTcp.h
  dtkDistributedCore.h
  dtkDistributedDiscoverer.h
  dtkDistributedCpu.h
  dtkDistributedGpu.h
  dtkDistributedNode.h
  dtkDistributor.h
  dtkDistributorController.h
  dtkDistributorScene.h
  dtkDistributorView.h)

set(${PROJECT_NAME}_SOURCES
  dtkDistributedCommunicator.cpp
  dtkDistributedCommunicatorTcp.cpp
  dtkDistributedCore.cpp
  dtkDistributedDiscoverer.cpp
  dtkDistributedDiscovererOar.cpp
  dtkDistributedDiscovererTorque.cpp
  dtkDistributedCpu.cpp
  dtkDistributedGpu.cpp
  dtkDistributedNode.cpp
  dtkDistributor.cpp
  dtkDistributorController.cpp
  dtkDistributorScene.cpp
  dtkDistributorView.cpp)

set(${PROJECT_NAME}_RESOURCES dtkDistributed.qrc)

## #################################################################
## Mpi sources
## #################################################################

if(MPI_FOUND)
set(${PROJECT_NAME}_HEADERS ${${PROJECT_NAME}_HEADERS}
  dtkDistributedCommunicatorMpi.h)
set(${PROJECT_NAME}_HEADERS_MOC ${${PROJECT_NAME}_HEADERS_MOC}
  dtkDistributedCommunicatorMpi.h)
set(${PROJECT_NAME}_SOURCES ${${PROJECT_NAME}_SOURCES}
  dtkDistributedCommunicatorMpi.cpp)
endif(MPI_FOUND)

## #################################################################
## Build rules
## #################################################################

add_definitions(${QT_DEFINITIONS})
add_definitions(-DQT_SHARED)
add_definitions(-DQT_NO_DEBUG)

qt4_wrap_cpp(${PROJECT_NAME}_SOURCES_MOC ${${PROJECT_NAME}_HEADERS_MOC})
qt4_add_RESOURCES(${PROJECT_NAME}_SOURCES_QRC ${${PROJECT_NAME}_RESOURCES})

add_library(${PROJECT_NAME} SHARED
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_SOURCES_MOC}
  ${${PROJECT_NAME}_SOURCES_QRC})

target_link_libraries(${PROJECT_NAME}
  ${QT_LIBRARIES}
  dtkCore
  dtkGui)

if(MPI_FOUND)
target_link_libraries(${PROJECT_NAME}
  ${MPI_LIBRARIES})
endif(MPI_FOUND)

## #################################################################
## Installation
## #################################################################

install(FILES ${${PROJECT_NAME}_HEADERS} DESTINATION include/${PROJECT_NAME})
install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)

