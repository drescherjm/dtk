### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Mon Feb 15 09:10:57 2010 (+0100)
## Version: $Id$
## Last-Updated: mar. sept. 20 13:01:38 2011 (+0200)
##           By: Nicolas Niclausse
##     Update #: 196
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
  dtkDistributedSlave.h
  dtkDistributedController.h
  dtkDistributedControllerStatusModel.h
  dtkDistributedControllerStatusModelItem.h
  dtkDistributedControllerStatusView.h
  dtkDistributedCore.h
  dtkDistributedCpu.h
  dtkDistributedExport.h
  dtkDistributedGpu.h
  dtkDistributedNode.h
  dtkDistributedServer.h
  dtkDistributedServerDaemon.h
  dtkDistributedServerManager.h
  dtkDistributedServerManagerOar.h
  dtkDistributedServerManagerTorque.h
  dtkDistributedService.h
  dtkDistributedSocket.h)

set(${PROJECT_NAME}_HEADERS_MOC
  dtkDistributedCommunicator.h
  dtkDistributedCommunicatorTcp.h
  dtkDistributedSlave.h
  dtkDistributedController.h
  dtkDistributedControllerStatusModel.h
  dtkDistributedControllerStatusView.h
  dtkDistributedCore.h
  dtkDistributedCpu.h
  dtkDistributedGpu.h
  dtkDistributedJob.h
  dtkDistributedNode.h
  dtkDistributedServerDaemon.h
  dtkDistributedServerManager.h
  dtkDistributedServerManagerOar.h
  dtkDistributedServerManagerTorque.h
  dtkDistributedService_p.h
  dtkDistributedSocket.h)

set(${PROJECT_NAME}_SOURCES
  dtkDistributedCommunicator.cpp
  dtkDistributedCommunicatorTcp.cpp
  dtkDistributedSlave.cpp
  dtkDistributedController.cpp
  dtkDistributedControllerStatusModel.cpp
  dtkDistributedControllerStatusModelItem.cpp
  dtkDistributedControllerStatusView.cpp
  dtkDistributedCore.cpp
  dtkDistributedCpu.cpp
  dtkDistributedGpu.cpp
  dtkDistributedJob.cpp
  dtkDistributedNode.cpp
  dtkDistributedServer.cpp
  dtkDistributedServerDaemon.cpp
  dtkDistributedServerManager.cpp
  dtkDistributedServerManagerOar.cpp
  dtkDistributedServerManagerTorque.cpp
  dtkDistributedService.cpp
  dtkDistributedSocket.cpp)

## #################################################################
## Platform specific sources
## #################################################################

if(WIN32)

set(${PROJECT_NAME}_HEADERS_MOC
  ${${PROJECT_NAME}_HEADERS_MOC}
  dtkDistributedServiceWin_p.h)

set(${PROJECT_NAME}_SOURCES
  ${${PROJECT_NAME}_SOURCES}
  dtkDistributedServiceWin.cpp)

else(WIN32)

set(${PROJECT_NAME}_HEADERS_MOC
  ${${PROJECT_NAME}_HEADERS_MOC}
  dtkDistributedServiceUnix_p.h
  dtkDistributedUnixServerSocket.h
  dtkDistributedUnixSocket.h)

set(${PROJECT_NAME}_SOURCES
  ${${PROJECT_NAME}_SOURCES}
  dtkDistributedServiceUnix.cpp
  dtkDistributedUnixServerSocket.cpp
  dtkDistributedUnixSocket.cpp)

endif(WIN32)

## #################################################################
## Mpi sources
## #################################################################

if(USE_MPI AND MPI_FOUND)
set(${PROJECT_NAME}_HEADERS ${${PROJECT_NAME}_HEADERS}
  dtkDistributedCommunicatorMpi.h)
set(${PROJECT_NAME}_HEADERS_MOC ${${PROJECT_NAME}_HEADERS_MOC}
  dtkDistributedCommunicatorMpi.h)
set(${PROJECT_NAME}_SOURCES ${${PROJECT_NAME}_SOURCES}
  dtkDistributedCommunicatorMpi.cpp)
endif(USE_MPI AND MPI_FOUND)

## #################################################################
## Build rules
## #################################################################

add_definitions(${QT_DEFINITIONS})
add_definitions(-DQT_SHARED)
if(NOT MSVC)
  add_definitions(-DQT_NO_DEBUG)
endif(NOT MSVC)

qt4_wrap_cpp(${PROJECT_NAME}_SOURCES_MOC ${${PROJECT_NAME}_HEADERS_MOC})

if(DTK_USE_PRECOMPILED_HEADERS)
  add_precompiled_header(${PROJECT_NAME}_SOURCES_PCH 
    "dtkPch/dtkPch.h" "../dtkPch/dtkPch.cpp" 
    ${${PROJECT_NAME}_SOURCES}
    ${${PROJECT_NAME}_HEADERS}
    ${${PROJECT_NAME}_SOURCES_MOC})
endif(DTK_USE_PRECOMPILED_HEADERS)

if(BUILD_SHARED_LIBS)

add_library(${PROJECT_NAME} SHARED
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_HEADERS}
  ${${PROJECT_NAME}_SOURCES_PCH}
  ${${PROJECT_NAME}_SOURCES_MOC})

else(BUILD_SHARED_LIBS)

add_library(${PROJECT_NAME} STATIC
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_HEADERS}
  ${${PROJECT_NAME}_SOURCES_PCH}
  ${${PROJECT_NAME}_SOURCES_MOC})

endif(BUILD_SHARED_LIBS)

target_link_libraries(${PROJECT_NAME}
  ${QT_LIBRARIES}
  dtkCore
  dtkJson
  dtkGui)

if(USE_MPI AND MPI_FOUND)
target_link_libraries(${PROJECT_NAME} ${MPI_LIBRARIES})
endif(USE_MPI AND MPI_FOUND)

## #################################################################
## Source file layout in development environments like Visual Studio
## #################################################################

SOURCE_GROUP("Header Files" REGULAR_EXPRESSION .*\\.h\$)
SOURCE_GROUP("Generated Files" FILES ${${PROJECT_NAME}_SOURCES_MOC} ${${PROJECT_NAME}_SOURCES_QRC})

## #################################################################
## Installation
## #################################################################

foreach(header ${${PROJECT_NAME}_HEADERS})
  string(REGEX REPLACE "(.*)\\.h\$" "\\1" h ${header})
  set(${PROJECT_NAME}_HEADERS_QTS "${${PROJECT_NAME}_HEADERS_QTS}" ${h})
endforeach(header)

install(FILES ${${PROJECT_NAME}_HEADERS} DESTINATION include/${PROJECT_NAME})
install(FILES ${${PROJECT_NAME}_HEADERS_QTS} DESTINATION include/${PROJECT_NAME})
install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)
