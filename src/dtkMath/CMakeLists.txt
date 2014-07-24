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

######################################################################
### CMakeLists.txt ends here
