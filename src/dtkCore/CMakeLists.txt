### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Created: Fri Feb  8 16:49:52 2013 (+0100)
## Version: 
## Last-Updated: Tue Feb 26 14:58:04 2013 (+0100)
##           By: Julien Wintz
##     Update #: 15
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
  dtkCorePluginManager.h
  dtkCoreSettings.h)

set(${PROJECT_NAME}_SOURCES
  dtkCorePluginManager.cpp
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
