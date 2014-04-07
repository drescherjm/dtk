### CMakeLists.txt ---
## 
## Author: Julien Wintz
## Created: Mon Jul 15 15:55:43 2013 (+0200)
## Version: 
## Last-Updated: lun. avril  7 11:13:07 2014 (+0200)
##           By: Nicolas Niclausse
##     Update #: 38
######################################################################
## 
### Change Log:
## 
######################################################################

project(dtkMath)

## #################################################################
## Input
## #################################################################

set(${PROJECT_NAME}_HEADERS
  dtkArray.h
  dtkArray.tpp
  dtkMath
  dtkMath.h
  dtkMatrix
  dtkMatrix.h
  dtkMatrix.tpp)

set(${PROJECT_NAME}_SOURCES
  dtkArray.cpp
  dtkMath.cpp
  dtkMatrix.cpp)

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
    COMPONENT math)

## ###################################################################
## Install rules - targets
## ###################################################################

install(TARGETS ${PROJECT_NAME}
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
      COMPONENT math
         EXPORT dtkDepends)
