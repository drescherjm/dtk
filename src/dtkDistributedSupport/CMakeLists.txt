### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Mon Feb 15 09:10:57 2010 (+0100)
## Version: $Id$
## Last-Updated: lun. févr.  3 16:23:13 2014 (+0100)
##           By: Nicolas Niclausse
##     Update #: 254
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

project(dtkDistributedSupport)

## #################################################################
## Sources
## #################################################################

set(${PROJECT_NAME}_HEADERS
  dtkDistributedCommunicator.h
  dtkDistributedCommunicatorTcp.h
  dtkDistributedSlave.h
  dtkDistributedController.h
  dtkDistributedControllerFilterView.h
  dtkDistributedControllerHeaderView.h
  dtkDistributedControllerJobView.h
  dtkDistributedControllerStatusModel.h
  dtkDistributedControllerStatusModelFilter.h
  dtkDistributedControllerStatusModelItem.h
  dtkDistributedControllerStatusView.h
  dtkDistributedControllerSubmitView.h
  dtkDistributedControllerTargetView.h
  dtkDistributedControllerTargetViewDelegate.h
  dtkDistributedCore.h
  dtkDistributedCpu.h
  dtkDistributedGpu.h
  dtkDistributedMessage.h
  dtkDistributedMimeData.h
  dtkDistributedNode.h
  dtkDistributedServer.h
  dtkDistributedServerDaemon.h
  dtkDistributedServerManager.h
  dtkDistributedServerManagerOar.h
  dtkDistributedServerManagerSsh.h
  dtkDistributedServerManagerTorque.h
  dtkDistributedService.h
  dtkDistributedSocket.h
  dtkDistributor.h)

set(${PROJECT_NAME}_SOURCES
  dtkDistributedCommunicator.cpp
  dtkDistributedCommunicatorTcp.cpp
  dtkDistributedSlave.cpp
  dtkDistributedController.cpp
  dtkDistributedControllerFilterView.cpp
  dtkDistributedControllerHeaderView.cpp
  dtkDistributedControllerJobView.cpp
  dtkDistributedControllerStatusModel.cpp
  dtkDistributedControllerStatusModelFilter.cpp
  dtkDistributedControllerStatusModelItem.cpp
  dtkDistributedControllerStatusView.cpp
  dtkDistributedControllerSubmitView.cpp
  dtkDistributedControllerTargetView.cpp
  dtkDistributedControllerTargetViewDelegate.cpp
  dtkDistributedCore.cpp
  dtkDistributedCpu.cpp
  dtkDistributedGpu.cpp
  dtkDistributedJob.cpp
  dtkDistributedMessage.cpp
  dtkDistributedMimeData.cpp
  dtkDistributedNode.cpp
  dtkDistributedServer.cpp
  dtkDistributedServerDaemon.cpp
  dtkDistributedServerManager.cpp
  dtkDistributedServerManagerOar.cpp
  dtkDistributedServerManagerSsh.cpp
  dtkDistributedServerManagerTorque.cpp
  dtkDistributedService.cpp
  dtkDistributedSocket.cpp
  dtkDistributor.cpp)

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

if(DTK_HAVE_MPI)
set(${PROJECT_NAME}_HEADERS ${${PROJECT_NAME}_HEADERS}
  dtkDistributedCommunicatorMpi.h)
set(${PROJECT_NAME}_HEADERS_MOC ${${PROJECT_NAME}_HEADERS_MOC}
  dtkDistributedCommunicatorMpi.h)
set(${PROJECT_NAME}_SOURCES ${${PROJECT_NAME}_SOURCES}
  dtkDistributedCommunicatorMpi.cpp)
endif(DTK_HAVE_MPI)


add_library(${PROJECT_NAME}
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_HEADERS}
)

qt5_use_modules(${PROJECT_NAME} Widgets)
qt5_use_modules(${PROJECT_NAME} Network)
qt5_use_modules(${PROJECT_NAME} Xml)

target_link_libraries(${PROJECT_NAME}
  dtkCoreSupportSupport
  dtkGui
  dtkLog)

if(DTK_HAVE_MPI)
target_link_libraries(${PROJECT_NAME} ${MPI_LIBRARIES})
endif(DTK_HAVE_MPI)

## #################################################################
## Export header file
## #################################################################

add_compiler_export_flags()

generate_export_header(${PROJECT_NAME}
  EXPORT_FILE_NAME "${PROJECT_NAME}Export.h")

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
  COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different "${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}Export.h" "${CMAKE_BINARY_DIR}"
  COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different "${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}Export.h" "${CMAKE_BINARY_DIR}/${PROJECT_NAME}Export")

set(${PROJECT_NAME}_HEADERS
  ${${PROJECT_NAME}_HEADERS}
 "${CMAKE_BINARY_DIR}/${PROJECT_NAME}Export.h")

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
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
