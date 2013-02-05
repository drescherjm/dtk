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
  dtkDistributedCommunicatorPlugin
  dtkDistributedCommunicatorPlugin.h
  dtkDistributedCommunicatorPluginManager
  dtkDistributedCommunicatorPluginManager.h
  dtkDistributedContainer.h
  dtkDistributedContainer.tpp)

set(${PROJECT_NAME}_SOURCES
  dtkDistributedCommunicatorPluginManager.cpp)

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

## ###################################################################
## Install rules
## ###################################################################

install(  FILES ${${PROJECT_NAME}_HEADERS} DESTINATION include/dtkDistributed)
install(TARGETS   ${PROJECT_NAME}          DESTINATION lib)
