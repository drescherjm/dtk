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

######################################################################
### CMakeLists.txt ends here
