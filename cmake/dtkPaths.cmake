### dtkPaths.cmake --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Fri Apr  2 09:10:51 2010 (+0200)
## Version: $Id$
## Last-Updated: Fri Apr  2 12:20:43 2010 (+0200)
##           By: Julien Wintz
##     Update #: 18
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
####################################################################x##

## #################################################################
## Setup input/output paths
## #################################################################

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  if(WIN32)
    string(REPLACE "\\" "/" ProgramFiles "$ENV{ProgramFiles}")
    set(CMAKE_INSTALL_PREFIX "${ProgramFiles}/Inria/${PROJECT_NAME}" CACHE PATH "dtk install prefix" FORCE)
  else(WIN32)
    set(CMAKE_INSTALL_PREFIX "/usr/local/inria" CACHE PATH "dtk install prefix" FORCE)
  endif(WIN32)
endif(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

if(WIN32)
  set(${PROJECT_NAME}_ARCHIVE_OUTPUT_DIRECTORY lib)
  set(${PROJECT_NAME}_RUNTIME_OUTPUT_DIRECTORY bin)
  set(${PROJECT_NAME}_LIBRARY_OUTPUT_DIRECTORY bin)
else(WIN32)
  set(${PROJECT_NAME}_ARCHIVE_OUTPUT_DIRECTORY lib)
  set(${PROJECT_NAME}_RUNTIME_OUTPUT_DIRECTORY bin)
  set(${PROJECT_NAME}_LIBRARY_OUTPUT_DIRECTORY lib)
endif(WIN32)

set(CMAKE_DEBUG_POSTFIX "d")

set(LIBRARY_OUTPUT_PATH    ${CMAKE_BINARY_DIR}/${${PROJECT_NAME}_LIBRARY_OUTPUT_DIRECTORY})
set(ARCHIVE_OUTPUT_PATH    ${CMAKE_BINARY_DIR}/${${PROJECT_NAME}_ARCHIVE_OUTPUT_DIRECTORY})
set(RUNTIME_OUTPUT_PATH    ${CMAKE_BINARY_DIR}/${${PROJECT_NAME}_RUNTIME_OUTPUT_DIRECTORY})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/${${PROJECT_NAME}_RUNTIME_OUTPUT_DIRECTORY})

set(${PROJECT_NAME}_INCLUDE_PATH ${CMAKE_SOURCE_DIR}/src)

set(${PROJECT_NAME}_LIBRARY_DIRS ${LIBRARY_OUTPUT_PATH})
set(${PROJECT_NAME}_RUNTIME_DIRS ${RUNTIME_OUTPUT_PATH})

include_directories(${${PROJECT_NAME}_INCLUDE_PATH})
