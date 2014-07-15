## Version: $Id$
##
######################################################################
##
### Commentary:
##
######################################################################
##
### Change Log:
##
######################################################################
##
### Code:

project(dtkDistributed)

## #################################################################
## Input
## #################################################################

set(${PROJECT_NAME}_HEADERS
  dtkDistributed
  dtkDistributed.h
  dtkDistributedArray
  dtkDistributedArray.h
  dtkDistributedArray.tpp
  dtkDistributedArrayCache
  dtkDistributedArrayCache.h
  dtkDistributedArrayData
  dtkDistributedArrayData.h
  dtkDistributedArrayNavigator
  dtkDistributedArrayNavigator.h
  dtkDistributedCommunicator
  dtkDistributedCommunicator.h
  dtkDistributedCommunicatorStatus.h
  dtkDistributedContainer.h
  dtkDistributedController.h
  dtkDistributedGraph
  dtkDistributedGraph.h
  dtkDistributedGraph.tpp
  dtkDistributedItem.h
  dtkDistributedLocalMessage.h
  dtkDistributedMapper
  dtkDistributedMapper.h
  dtkDistributedMessage.h
  dtkDistributedPolicy
  dtkDistributedPolicy.h
  dtkDistributedResourceManager.h
  dtkDistributedResourceManagerLocal.h
  dtkDistributedResourceManagerOar.h
  dtkDistributedResourceManagerTorque.h
  dtkDistributedServerDaemon.h
  dtkDistributedSettings
  dtkDistributedSettings.h
  dtkDistributedSlave.h
  dtkDistributedWork
  dtkDistributedWork.h
  dtkDistributedWorker
  dtkDistributedWorker.h
  dtkDistributedWorkerManager
  dtkDistributedWorkerManager.h)

set(${PROJECT_NAME}_SOURCES
  dtkDistributed.cpp
  dtkDistributedCommunicator.cpp
  dtkDistributedCommunicatorStatus.cpp
  dtkDistributedController.cpp
  dtkDistributedLocalMessage.cpp
  dtkDistributedMapper.cpp
  dtkDistributedMessage.cpp
  dtkDistributedPolicy.cpp
  dtkDistributedResourceManager.cpp
  dtkDistributedResourceManagerLocal.cpp
  dtkDistributedResourceManagerOar.cpp
  dtkDistributedResourceManagerTorque.cpp
  dtkDistributedServerDaemon.cpp
  dtkDistributedSettings.cpp
  dtkDistributedSlave.cpp
  dtkDistributedWork.cpp
  dtkDistributedWorker.cpp
  dtkDistributedWorkerManager.cpp)

## #################################################################
## Build rules
## #################################################################

add_library(${PROJECT_NAME} SHARED
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_HEADERS})

## ###################################################################
## Link rules
## ###################################################################

qt5_use_modules(${PROJECT_NAME} Core)
qt5_use_modules(${PROJECT_NAME} Network)
qt5_use_modules(${PROJECT_NAME} Xml)

target_link_libraries(${PROJECT_NAME} dtkCore)
target_link_libraries(${PROJECT_NAME} dtkLog)

## ###################################################################
## Install rules - files
## ###################################################################

install(FILES ${${PROJECT_NAME}_HEADERS}
  DESTINATION include/${PROJECT_NAME}
    COMPONENT distributed)

## ###################################################################
## Install rules - targets
## ###################################################################

install(TARGETS ${PROJECT_NAME}
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
      COMPONENT distributed
         EXPORT dtkDepends)

######################################################################
### CMakeLists.txt ends here
