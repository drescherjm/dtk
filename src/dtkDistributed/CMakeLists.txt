### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Created: Mon Feb  4 12:16:39 2013 (+0100)
## Version: 
## Last-Updated: 2013 Mon Feb  4 16:03:57 (+0100)
##           By: Thibaud Kloczko
##     Update #: 16
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
  dtkDistributedCommunicatorPlugin.h
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
