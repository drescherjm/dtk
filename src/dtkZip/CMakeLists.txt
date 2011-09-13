### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008-2011 - Julien Wintz, Inria.
## Created: Tue Jun 21 12:08:14 2011 (+0200)
## Version: $Id$
## Last-Updated: Thu Sep  8 14:40:29 2011 (+0200)
##           By: Julien Wintz
##     Update #: 39
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

if(ZLIB_FOUND)

## #################################################################

project(dtkZip)

## #################################################################
## Sources
## #################################################################

set(${PROJECT_NAME}_HEADERS
  dtkZip.h
  dtkZipExport.h
  dtkZipFile.h
  dtkZipFileInfo.h
  dtkZipNewInfo.h
  dtkZipUtils.h)

set(${PROJECT_NAME}_HEADERS_MOC
  dtkZipFile.h)

set(${PROJECT_NAME}_SOURCES
  dtkZip.cpp
  dtkZipFile.cpp
  dtkZipNewInfo.cpp
  dtkZipUtils.cpp)

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

if(BUILD_SHARED_LIBS)

add_library(${PROJECT_NAME} SHARED
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_HEADERS}
  ${${PROJECT_NAME}_SOURCES_MOC})

else(BUILD_SHARED_LIBS)

add_library(${PROJECT_NAME} STATIC
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_HEADERS}
  ${${PROJECT_NAME}_SOURCES_MOC})

endif(BUILD_SHARED_LIBS)

target_link_libraries(${PROJECT_NAME}
  ${QT_LIBRARIES}
  ${ZLIB_LIBRARIES})

## #################################################################
## Source file layout in development environments like Visual Studio
## #################################################################

SOURCE_GROUP("Header Files" REGULAR_EXPRESSION .*\\.h\$)
SOURCE_GROUP("Generated Files" FILES ${${PROJECT_NAME}_SOURCES_MOC})

## #################################################################
## Installation
## #################################################################

foreach(header ${${PROJECT_NAME}_HEADERS})
  string(REGEX REPLACE "(.*)\\.h\$" "\\1" h ${header})
  set(${PROJECT_NAME}_HEADERS_QTS "${${PROJECT_NAME}_HEADERS_QTS}" ${h})
endforeach(header)

install(FILES ${${PROJECT_NAME}_HEADERS} DESTINATION include/${PROJECT_NAME})
install(FILES ${${PROJECT_NAME}_HEADERS_QTS} DESTINATION include/${PROJECT_NAME})
install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)

## #################################################################

endif(ZLIB_FOUND)
