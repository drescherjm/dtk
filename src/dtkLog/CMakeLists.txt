### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Created: Mon Feb 11 19:23:24 2013 (+0100)
## Version: 
## Last-Updated: Tue Feb 26 14:58:42 2013 (+0100)
##           By: Julien Wintz
##     Update #: 22
######################################################################
## 
### Change Log:
## 
######################################################################

project(dtkLog)

## #################################################################
## Input
## #################################################################

set(${PROJECT_NAME}_HEADERS
  dtkLogger.h
  dtkLogger_p.h)

set(${PROJECT_NAME}_SOURCES
  dtkLogger.cpp)

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
    COMPONENT log)

## ###################################################################
## Install rules - targets
## ###################################################################

install(TARGETS ${PROJECT_NAME}
    DESTINATION lib
      COMPONENT log
         EXPORT dtkDepends)
