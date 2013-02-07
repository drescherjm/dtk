### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Created: Mon Feb  4 12:16:39 2013 (+0100)
## Version: 
## Last-Updated: 2013 Thu Feb  7 12:25:52 (+0100)
##           By: Thibaud Kloczko
##     Update #: 32
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
  dtkDistributedContainer.tpp
  dtkDistributedMapper.h)

set(${PROJECT_NAME}_SOURCES
  dtkDistributedCommunicatorPluginManager.cpp
  dtkDistributedMapper.cpp)

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
