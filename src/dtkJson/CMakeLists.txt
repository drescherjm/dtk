### CMakeLists.txt ---
##
## Author: Nicolas Niclausse
## Copyright (C) 2011 - Nicolas Niclausse, Inria.
## Created: ven. août  5 09:57:25 2011 (+0200)
## Version: $Id$
## Last-Updated: ven. août  5 10:00:01 2011 (+0200)
##           By: Nicolas Niclausse
##     Update #: 11
######################################################################
##
### Commentary:
##
######################################################################
##
### Change log:
##
######################################################################

project(dtkJson)

## #################################################################
## Sources
## #################################################################

set(${PROJECT_NAME}_HEADERS
  dtkJson.h)

set(${PROJECT_NAME}_HEADERS_MOC
  dtkJson.h)

set(${PROJECT_NAME}_SOURCES
  dtkJson.cpp)

## #################################################################
## Build rules
## #################################################################
if(NOT WIN32)
add_definitions(-Wno-write-strings)
add_definitions(-Wformat=0)
endif(NOT WIN32)

add_definitions(${QT_DEFINITIONS})
add_definitions(-DQT_SHARED)

if(NOT WIN32)
  add_definitions(-DQT_NO_DEBUG)
endif(NOT WIN32)

qt4_wrap_cpp(${PROJECT_NAME}_SOURCES_MOC ${${PROJECT_NAME}_HEADERS_MOC})

add_library(${PROJECT_NAME} SHARED
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_HEADERS}
  ${${PROJECT_NAME}_SOURCES_MOC})

target_link_libraries(${PROJECT_NAME}
  ${QT_LIBRARIES})

## #################################################################
## Source file layout in development environments like Visual Studio
## #################################################################

SOURCE_GROUP("Header Files" REGULAR_EXPRESSION .*\\.h\$)
SOURCE_GROUP("Generated Files" FILES ${${PROJECT_NAME}_SOURCES_MOC})

## #################################################################
## Installation
## #################################################################

install(FILES ${${PROJECT_NAME}_HEADERS} DESTINATION include/${PROJECT_NAME})
install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)

## #################################################################


