 ### CMakeLists.txt ---
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Mon Jul 20 18:30:43 2009 (+0200)
## Version: $Id$
## Last-Updated: Tue Sep 18 09:13:11 2012 (+0200)
##           By: Julien Wintz
##     Update #: 391
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

cmake_minimum_required(VERSION 2.8.6)

project(dtk)

set(${PROJECT_NAME}_VERSION_MAJOR 0 CACHE STRING "dtk major version number.")
set(${PROJECT_NAME}_VERSION_MINOR 6 CACHE STRING "dtk minor version number.")
set(${PROJECT_NAME}_VERSION_BUILD 0 CACHE STRING "dtk build version number.")

set(${PROJECT_NAME}_VERSION
  "${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}.${${PROJECT_NAME}_VERSION_BUILD}")

mark_as_advanced(${PROJECT_NAME}_VERSION_MAJOR)
mark_as_advanced(${PROJECT_NAME}_VERSION_MINOR)
mark_as_advanced(${PROJECT_NAME}_VERSION_BUILD)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

option(BUILD_SHARED_LIBS       "Build shared libraries"  true)
option(DTK_BUILD_TOOLS         "Build tools"             true)
option(DTK_BUILD_EXAMPLES      "Build examples"          false)
option(DTK_BUILD_TESTING       "Build testing"           false)
option(DTK_BUILD_DOCUMENTATION "Build documentation"     false)
option(DTK_BUILD_WRAPPERS      "Build wrappers"          false)
option(DTK_BUILD_REPORTING     "Build reporting"         false)
option(DTK_BUILD_TUTORIALS     "Build tutorials"         false)
option(DTK_BUILD_MPI           "Build mpi related code"  false)

option(DTK_BUILD_DISTRIBUTED   "Build distributed layer" true)
option(DTK_BUILD_COMPOSER      "Build composer layer"    true)
option(DTK_BUILD_VR            "Build vr layer"          true)
option(DTK_BUILD_PLOT          "Build plotting layer"    true)
option(DTK_BUILD_SCRIPT        "Build scripting layer"   true)

message ("Configuration of dtk:")
message ("  DTK_BUILD_TOOLS ${DTK_BUILD_TOOLS}")
message ("  DTK_BUILD_EXAMPLES ${DTK_BUILD_EXAMPLES}")
message ("  DTK_BUILD_TESTING ${DTK_BUILD_TESTING}")
message ("  DTK_BUILD_DOCUMENTATION ${DTK_BUILD_DOCUMENTATION}")
message ("  DTK_BUILD_TUTORIALS ${DTK_BUILD_TUTORIALS}")
message ("  DTK_BUILD_WRAPPERS ${DTK_BUILD_WRAPPERS}")
message ("  DTK_BUILD_REPORTING ${DTK_BUILD_REPORTING}")

if(MSVC)
  option(DTK_USE_PRECOMPILED_HEADERS "Use precompiled headers" true)
endif(MSVC)

include(dtkDependencies)
include(dtkBuild)
if (DTK_CPACK)
  include(dtkPack)
endif (DTK_CPACK)
include(dtkPch)

add_subdirectory(include)
add_subdirectory(src)

if(DTK_BUILD_TOOLS)
  add_subdirectory(tools)
endif(DTK_BUILD_TOOLS)

if(DTK_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif(DTK_BUILD_EXAMPLES)

if(DTK_BUILD_REPORTING)
  include(dtkReporting)
endif(DTK_BUILD_REPORTING)

if(DTK_BUILD_TESTING)
  add_subdirectory(tests)
endif(DTK_BUILD_TESTING)

if(DTK_BUILD_DOCUMENTATION)
  add_subdirectory(doc)
endif(DTK_BUILD_DOCUMENTATION)

if(DTK_BUILD_TUTORIALS)
  add_subdirectory(tutorials)
endif(DTK_BUILD_TUTORIALS)
