### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Created: Fri Feb  8 16:49:52 2013 (+0100)
## Version: 
## Last-Updated: Fri Mar 22 09:40:00 2013 (+0100)
##           By: Julien Wintz
##     Update #: 31
######################################################################
## 
### Change Log:
## 
######################################################################

project(dtkCore)

## #################################################################
## Input
## #################################################################

set(${PROJECT_NAME}_HEADERS
  dtkCore
  dtkCore.h
  dtkCoreObject
  dtkCoreObject.h
  dtkCorePlugin
  dtkCorePlugin.h
  dtkCorePluginFactory
  dtkCorePluginFactory.h
  dtkCorePluginFactory.tpp
  dtkCorePluginManager
  dtkCorePluginManager.h
  dtkCorePluginManager.tpp
  dtkCoreSettings
  dtkCoreSettings.h)

set(${PROJECT_NAME}_SOURCES
  dtkCoreSettings.cpp)

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

## ###################################################################
## Install rules - files
## ###################################################################

install(FILES ${${PROJECT_NAME}_HEADERS}
  DESTINATION include/${PROJECT_NAME}
    COMPONENT core)

## ###################################################################
## Install rules - targets
## ###################################################################

install(TARGETS ${PROJECT_NAME}
    DESTINATION lib
      COMPONENT core
         EXPORT dtkDepends)

## ###################################################################
## Target export
## ###################################################################

list(APPEND DTK_TARGETS ${PROJECT_NAME})
