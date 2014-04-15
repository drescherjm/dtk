### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Created: Fri Feb  8 16:49:52 2013 (+0100)
## Version: 
## Last-Updated: mar. avril 15 11:07:38 2014 (+0200)
##           By: Thibaud Kloczko
##     Update #: 37
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
  dtkCorePlugin
  dtkCorePlugin.h
  dtkCorePluginFactory
  dtkCorePluginFactory.h
  dtkCorePluginFactory_t.h
  dtkCorePluginManager
  dtkCorePluginManager.h
  dtkCorePluginManager_t.h
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
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
      COMPONENT core
         EXPORT dtkDepends)
