### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Mon Jul 20 18:30:43 2009 (+0200)
## Version: $Id$
## Last-Updated: Thu Mar  3 19:07:20 2011 (+0100)
##           By: Julien Wintz
##     Update #: 300
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

cmake_minimum_required(VERSION 2.6.4)

project(dtk)



set(${PROJECT_NAME}_VERSION_MAJOR 0 CACHE STRING "dtk major version number.")
set(${PROJECT_NAME}_VERSION_MINOR 1 CACHE STRING "dtk minor version number.")
set(${PROJECT_NAME}_VERSION_BUILD 28 CACHE STRING "dtk build version number.")
set(${PROJECT_NAME}_VERSION
  "${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}.${${PROJECT_NAME}_VERSION_BUILD}")

mark_as_advanced(${PROJECT_NAME}_VERSION_MAJOR)
mark_as_advanced(${PROJECT_NAME}_VERSION_MINOR)
mark_as_advanced(${PROJECT_NAME}_VERSION_BUILD)

enable_testing()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

option(BUILD_SHARED_LIBS   "Build shared libraries" true)
option(BUILD_TOOLS         "Build tools"            true)
option(BUILD_EXAMPLES      "Build examples"         true)
option(BUILD_DOCUMENTATION "Build documentation"    true)
option(BUILD_WRAPPERS      "Build wrappers"         true)

include(dtkDependencies)
include(dtkBuild)
include(dtkNightly)
#include(dtkDart)
include(dtkPack)

# -----------------------------------------------------------------------------
# Include Dart/CTest for testing
# -----------------------------------------------------------------------------
include(Dart)
include(CTest)

add_subdirectory(src)

if(BUILD_TOOLS)
  add_subdirectory(tools)
endif(BUILD_TOOLS)

if(BUILD_EXAMPLES)
  add_subdirectory(examples)
endif(BUILD_EXAMPLES)

if(BUILD_DOCUMENTATION)
  add_subdirectory(doc)
endif(BUILD_DOCUMENTATION)


