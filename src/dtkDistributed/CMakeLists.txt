### CMakeLists.txt ---
##
## Author: Julien Wintz
## Created: Mon Feb  4 12:16:39 2013 (+0100)
######################################################################
##
### Change Log:
##
######################################################################

project(dtkDistributed)

## #################################################################
## Input
## #################################################################

set(${PROJECT_NAME}_HEADERS
  dtkDistributed
  dtkDistributed.h
  dtkDistributedCommunicator.h
  dtkDistributedCommunicatorPlugin
  dtkDistributedCommunicatorPlugin.h
  dtkDistributedCommunicatorPluginFactory
  dtkDistributedCommunicatorPluginFactory.h
  dtkDistributedCommunicatorPluginManager
  dtkDistributedCommunicatorPluginManager.h
  dtkDistributedContainer.h
  dtkDistributedContainer.tpp
  dtkDistributedMapper.h
  dtkDistributedPolicy.h
  dtkDistributedSettings
  dtkDistributedSettings.h
  dtkDistributedWork.h
  dtkDistributedWorker.h
  dtkDistributedWorkerManager.h)

set(${PROJECT_NAME}_SOURCES
  dtkDistributed.cpp
  dtkDistributedCommunicator.cpp
  dtkDistributedCommunicatorPluginFactory.cpp
  dtkDistributedCommunicatorPluginManager.cpp
  dtkDistributedMapper.cpp
  dtkDistributedPolicy.cpp
  dtkDistributedSettings.cpp
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

target_link_libraries(${PROJECT_NAME} dtkCore)

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
    DESTINATION lib
      COMPONENT distributed
         EXPORT dtkDepends)
