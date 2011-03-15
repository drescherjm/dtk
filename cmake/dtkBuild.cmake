### dtkBuild.cmake --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Fri Apr  2 09:05:55 2010 (+0200)
## Version: $Id$
## Last-Updated: Tue Mar 15 17:27:44 2011 (+0100)
##           By: Julien Wintz
##     Update #: 175
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

## #################################################################
## Configure cmake variables
## #################################################################

set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type")

set(CMAKE_COLOR_MAKEFILE ON)
set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)

mark_as_advanced(CMAKE_BACKWARDS_COMPATIBILITY)
mark_as_advanced(CMAKE_BUILD_TYPE)
mark_as_advanced(CMAKE_INSTALL_PREFIX)
if(APPLE)
  mark_as_advanced(CMAKE_OSX_ARCHITECTURES)
  mark_as_advanced(CMAKE_OSX_DEPLOYMENT_TARGET)
  mark_as_advanced(CMAKE_OSX_SYSROOT)
endif(APPLE)

## #################################################################
## Install prefix
## #################################################################

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  if(WIN32)
    string(REPLACE "\\" "/" ProgramFiles "$ENV{ProgramFiles}")
    set(CMAKE_INSTALL_PREFIX "${ProgramFiles}/Inria/${PROJECT_NAME}" CACHE PATH "${PROJECT_NAME} install prefix" FORCE)
  else(WIN32)
    set(CMAKE_INSTALL_PREFIX "/usr/local/inria/" CACHE PATH "${PROJECT_NAME} install prefix" FORCE)
  endif(WIN32)
endif(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

## #################################################################
## Configure arch
## #################################################################

if(CMAKE_SIZEOF_VOID_P MATCHES 8)
    set(DTK_PLATFORM_64 1)
else(CMAKE_SIZEOF_VOID_P MATCHES 8)
    set(DTK_PLATFORM_32 1)
endif(CMAKE_SIZEOF_VOID_P MATCHES 8)

configure_file (
  "${PROJECT_SOURCE_DIR}/src/dtkCore/dtkConfig.h.in"
  "${PROJECT_BINARY_DIR}/dtkConfig.h")

## #################################################################
## Configure path
## #################################################################

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_BINARY_DIR})

if(WIN32)
  set(${PROJECT_NAME}_ARCHIVE_OUTPUT_DIRECTORY lib)
  set(${PROJECT_NAME}_RUNTIME_OUTPUT_DIRECTORY bin)
  set(${PROJECT_NAME}_LIBRARY_OUTPUT_DIRECTORY bin)
else(WIN32)
  set(${PROJECT_NAME}_ARCHIVE_OUTPUT_DIRECTORY lib)
  set(${PROJECT_NAME}_RUNTIME_OUTPUT_DIRECTORY bin)
  set(${PROJECT_NAME}_LIBRARY_OUTPUT_DIRECTORY lib)
endif(WIN32)

set(LIBRARY_OUTPUT_PATH    ${CMAKE_BINARY_DIR}/${${PROJECT_NAME}_LIBRARY_OUTPUT_DIRECTORY})
set(ARCHIVE_OUTPUT_PATH    ${CMAKE_BINARY_DIR}/${${PROJECT_NAME}_ARCHIVE_OUTPUT_DIRECTORY})
set(RUNTIME_OUTPUT_PATH    ${CMAKE_BINARY_DIR}/${${PROJECT_NAME}_RUNTIME_OUTPUT_DIRECTORY})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/${${PROJECT_NAME}_RUNTIME_OUTPUT_DIRECTORY})

set(LIBRARY_INSTALL_OUTPUT_PATH    ${CMAKE_INSTALL_PREFIX}/${${PROJECT_NAME}_LIBRARY_OUTPUT_DIRECTORY})
set(ARCHIVE_INSTALL_OUTPUT_PATH    ${CMAKE_INSTALL_PREFIX}/${${PROJECT_NAME}_ARCHIVE_OUTPUT_DIRECTORY})
set(RUNTIME_INSTALL_OUTPUT_PATH    ${CMAKE_INSTALL_PREFIX}/${${PROJECT_NAME}_RUNTIME_OUTPUT_DIRECTORY})
set(EXECUTABLE_INSTALL_OUTPUT_PATH ${CMAKE_INSTALL_PREFIX}/${${PROJECT_NAME}_RUNTIME_OUTPUT_DIRECTORY})

set(${PROJECT_NAME}_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/src) 
set(${PROJECT_NAME}_LIBRARY_DIRS ${LIBRARY_OUTPUT_PATH})
set(${PROJECT_NAME}_RUNTIME_DIRS ${RUNTIME_OUTPUT_PATH})
set(${PROJECT_NAME}_CMAKE_DIRS ${CMAKE_SOURCE_DIR}/cmake)
set(${PROJECT_NAME}_USE_FILE ${CMAKE_BINARY_DIR}/${PROJECT_NAME}Use.cmake)

set(${PROJECT_NAME}_INSTALL_INCLUDE_DIRS ${CMAKE_INSTALL_PREFIX}/include) 
set(${PROJECT_NAME}_INSTALL_LIBRARY_DIRS ${LIBRARY_INSTALL_OUTPUT_PATH})
set(${PROJECT_NAME}_INSTALL_RUNTIME_DIRS ${RUNTIME_INSTALL_OUTPUT_PATH})
set(${PROJECT_NAME}_INSTALL_CMAKE_DIRS ${CMAKE_INSTALL_PREFIX}/cmake)
set(${PROJECT_NAME}_INSTALL_USE_FILE ${CMAKE_INSTALL_PREFIX}/cmake/${PROJECT_NAME}Use.cmake)

## #################################################################
## Setup configration files
## #################################################################

if(EXISTS ${CMAKE_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in)
configure_file( ## Build tree configure file
  ${CMAKE_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in
  ${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}Config.cmake
  @ONLY IMMEDIATE)
endif(EXISTS ${CMAKE_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in)

if(EXISTS ${CMAKE_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.install.cmake.in)
configure_file( ## Install tree configure file
  ${CMAKE_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.install.cmake.in
  ${${PROJECT_NAME}_BINARY_DIR}/install/${PROJECT_NAME}Config.cmake
  @ONLY IMMEDIATE)
endif(EXISTS ${CMAKE_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.install.cmake.in)

## #################################################################
## Setup find file
## #################################################################

string(TOUPPER ${PROJECT_NAME} FND_NAME)

if(EXISTS ${CMAKE_SOURCE_DIR}/cmake/Find${FND_NAME}.cmake.in)
configure_file( ## Build tree configure file
  ${CMAKE_SOURCE_DIR}/cmake/Find${FND_NAME}.cmake.in
  ${${PROJECT_NAME}_BINARY_DIR}/CMakeModules/Find${FND_NAME}.cmake
  @ONLY IMMEDIATE)
endif(EXISTS ${CMAKE_SOURCE_DIR}/cmake/Find${FND_NAME}.cmake.in)

## #################################################################
## Setup use file
## #################################################################

if(EXISTS ${CMAKE_SOURCE_DIR}/cmake/${PROJECT_NAME}Use.cmake.in)
configure_file( ## Common use file
  ${CMAKE_SOURCE_DIR}/cmake/${PROJECT_NAME}Use.cmake.in
  ${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}Use.cmake
  @ONLY IMMEDIATE)
endif(EXISTS ${CMAKE_SOURCE_DIR}/cmake/${PROJECT_NAME}Use.cmake.in)

## #################################################################
## Path relocation
## #################################################################

set(CMAKE_SKIP_BUILD_RPATH FALSE)

set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)

if (APPLE)
  set(CMAKE_INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/lib")
endif (APPLE)

if (UNIX AND NOT APPLE)
  set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
endif (UNIX AND NOT APPLE)

set(CMAKE_INSTALL_RPATH_USE_LINK_PATH FALSE)

## #################################################################
## Uninstall target
## #################################################################

if(EXISTS ${CMAKE_SOURCE_DIR}/cmake/${PROJECT_NAME}Uninstall.cmake.in)

configure_file("${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}Uninstall.cmake.in"
               "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Uninstall.cmake"
               IMMEDIATE @ONLY)

add_custom_target(uninstall
  "${CMAKE_COMMAND}" -P
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Uninstall.cmake")

endif(EXISTS ${CMAKE_SOURCE_DIR}/cmake/${PROJECT_NAME}Uninstall.cmake.in)

## #################################################################
## Install cmake files
## #################################################################

if( EXISTS ${${PROJECT_NAME}_SOURCE_DIR}/cmake/${PROJECT_NAME}Dependencies.cmake
AND EXISTS ${${PROJECT_NAME}_SOURCE_DIR}/cmake/${PROJECT_NAME}Build.cmake
AND EXISTS ${${PROJECT_NAME}_SOURCE_DIR}/cmake/${PROJECT_NAME}Pack.cmake
AND EXISTS ${${PROJECT_NAME}_BINARY_DIR}/install/${PROJECT_NAME}Config.cmake
AND EXISTS ${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}Use.cmake
AND EXISTS ${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}Uninstall.cmake)

install(FILES
  ${${PROJECT_NAME}_SOURCE_DIR}/cmake/${PROJECT_NAME}Dependencies.cmake
  ${${PROJECT_NAME}_SOURCE_DIR}/cmake/${PROJECT_NAME}Build.cmake
  ${${PROJECT_NAME}_SOURCE_DIR}/cmake/${PROJECT_NAME}Pack.cmake
  ${${PROJECT_NAME}_BINARY_DIR}/install/${PROJECT_NAME}Config.cmake
  ${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}Use.cmake
  ${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}Uninstall.cmake
  DESTINATION
  cmake)

endif( EXISTS ${${PROJECT_NAME}_SOURCE_DIR}/cmake/${PROJECT_NAME}Dependencies.cmake
   AND EXISTS ${${PROJECT_NAME}_SOURCE_DIR}/cmake/${PROJECT_NAME}Build.cmake
   AND EXISTS ${${PROJECT_NAME}_SOURCE_DIR}/cmake/${PROJECT_NAME}Pack.cmake
   AND EXISTS ${${PROJECT_NAME}_BINARY_DIR}/install/${PROJECT_NAME}Config.cmake
   AND EXISTS ${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}Use.cmake
   AND EXISTS ${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}Uninstall.cmake)

if(EXISTS ${${PROJECT_NAME}_SOURCE_DIR}/cmake/${PROJECT_NAME}Plugin.cmake)
install(FILES
  ${${PROJECT_NAME}_SOURCE_DIR}/cmake/${PROJECT_NAME}Plugin.cmake
  DESTINATION
  cmake)
endif(EXISTS ${${PROJECT_NAME}_SOURCE_DIR}/cmake/${PROJECT_NAME}Plugin.cmake)
