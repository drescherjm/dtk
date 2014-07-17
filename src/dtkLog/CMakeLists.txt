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

project(dtkLog)

## #################################################################
## Input
## #################################################################

set(${PROJECT_NAME}_HEADERS
  dtkLog
  dtkLog.h
  dtkLogger.h
  dtkLogger_p.h
  dtkLoggerHandlers.h)

set(${PROJECT_NAME}_SOURCES
  dtkLogger.cpp
  dtkLoggerHandlers.cpp)

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
## Target prooerties
## ###################################################################

if(APPLE)
set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_RPATH 1)
set_target_properties(${PROJECT_NAME} PROPERTIES
  INSTALL_NAME_DIR "@executable_path/../lib")
endif(APPLE)

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
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
      COMPONENT log
         EXPORT dtkDepends)

######################################################################
### CMakeLists.txt ends here
