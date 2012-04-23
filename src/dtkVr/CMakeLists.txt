### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Wed Jan 13 13:57:41 2010 (+0100)
## Version: $Id$
## Last-Updated: Mon Apr 16 12:13:48 2012 (+0200)
##           By: Julien Wintz
##     Update #: 299
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

project(dtkVr)

## #################################################################
## Sources
## #################################################################

set(${PROJECT_NAME}_HEADERS
  dtkVrDevice.h
  dtkVrFlystickRecognizer.h
  dtkVrGestureRecognizer.h
  dtkVrHeadRecognizer.h
  dtkVrScreen.h
  dtkVrTracker.h)

set(${PROJECT_NAME}_HEADERS_MOC
  dtkVrDevice.h
  dtkVrFlystickRecognizer.h
  dtkVrFlystickRecognizer_p.h
  dtkVrGestureRecognizer.h
  dtkVrGestureRecognizer_p.h
  dtkVrHeadRecognizer.h
  dtkVrHeadRecognizer_p.h
  dtkVrTracker.h)

set(${PROJECT_NAME}_SOURCES
  dtkVrDevice.cpp
  dtkVrFlystickRecognizer.cpp
  dtkVrGestureRecognizer.cpp
  dtkVrHeadRecognizer.cpp
  dtkVrScreen.cpp
  dtkVrTracker.cpp)

## #################################################################
## Vrpn sources
## #################################################################

if(QUAT_LIBRARIES AND VRPN_LIBRARIES AND MPI_FOUND)

add_definitions(-DDTK_WRAP_VR)

set(${PROJECT_NAME}_HEADERS ${${PROJECT_NAME}_HEADERS}
  dtkVrDeviceVrpn.h
  dtkVrManager.h
  dtkVrMaster.h
  dtkVrProcess.h
  dtkVrSlave.h
  dtkVrTrackerVrpn.h)

set(${PROJECT_NAME}_HEADERS_MOC ${${PROJECT_NAME}_HEADERS_MOC}
  dtkVrDeviceVrpn.h
  dtkVrManager.h
  dtkVrMaster.h
  dtkVrProcess.h
  dtkVrSlave.h
  dtkVrTrackerVrpn.h)

set(${PROJECT_NAME}_SOURCES ${${PROJECT_NAME}_SOURCES}
  dtkVrDeviceVrpn.cpp
  dtkVrManager.cpp
  dtkVrMaster.cpp
  dtkVrProcess.cpp
  dtkVrSlave.cpp
  dtkVrTrackerVrpn.cpp)

endif(QUAT_LIBRARIES AND VRPN_LIBRARIES AND MPI_FOUND)

## #################################################################
## Wrapping
## #################################################################

set(${PROJECT_NAME}_SOURCES_WRAP)

if(DTK_BUILD_WRAPPERS AND SWIG_FOUND)

  set(${PROJECT_NAME}_WRAP_DEPENDS ${${PROJECT_NAME}_HEADERS})
  
  if(PYTHONLIBS_FOUND)
    dtk_wrap(${PROJECT_NAME} ${PROJECT_NAME}_SOURCES_WRAP vr python ${CMAKE_CURRENT_SOURCE_DIR}/dtkVr.i ${${PROJECT_NAME}_WRAP_DEPENDS})
  endif(PYTHONLIBS_FOUND)

  if(TCL_FOUND)
    dtk_wrap(${PROJECT_NAME} ${PROJECT_NAME}_SOURCES_WRAP vr tcl    ${CMAKE_CURRENT_SOURCE_DIR}/dtkVr.i ${${PROJECT_NAME}_WRAP_DEPENDS})
  endif(TCL_FOUND)

endif(DTK_BUILD_WRAPPERS AND SWIG_FOUND)

## #################################################################
## Build rules
## #################################################################

if(NOT WIN32)
add_definitions(-Wno-write-strings)
endif(NOT WIN32)

add_definitions(${QT_DEFINITIONS})
add_definitions(-DQT_SHARED)
if(NOT MSVC)
  add_definitions(-DQT_NO_DEBUG)
endif(NOT MSVC)

qt4_wrap_cpp(${PROJECT_NAME}_SOURCES_MOC ${${PROJECT_NAME}_HEADERS_MOC})

if(DTK_USE_PRECOMPILED_HEADERS)
  add_precompiled_header(${PROJECT_NAME}_SOURCES_PCH 
    "dtkPch/dtkPch.h" "../dtkPch/dtkPch.cpp" 
    ${${PROJECT_NAME}_SOURCES}
    ${${PROJECT_NAME}_HEADERS}
    ${${PROJECT_NAME}_SOURCES_MOC}
    ${${PROJECT_NAME}_SOURCES_WRAP})
endif(DTK_USE_PRECOMPILED_HEADERS)

if(BUILD_SHARED_LIBS)

add_library(${PROJECT_NAME} SHARED
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_HEADERS}
  ${${PROJECT_NAME}_SOURCES_MOC}
  ${${PROJECT_NAME}_SOURCES_PCH}
  ${${PROJECT_NAME}_SOURCES_WRAP})

else(BUILD_SHARED_LIBS)

add_library(${PROJECT_NAME} STATIC
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_HEADERS}
  ${${PROJECT_NAME}_SOURCES_MOC}
  ${${PROJECT_NAME}_SOURCES_PCH}
  ${${PROJECT_NAME}_SOURCES_WRAP})

endif(BUILD_SHARED_LIBS)

target_link_libraries(${PROJECT_NAME}
  dtkMath
  dtkCore
  dtkDistributed
  dtkLog)

if(MSVC)
  target_link_libraries(${PROJECT_NAME} wsock32)
endif()

if(MPI_FOUND)
  target_link_libraries(${PROJECT_NAME} ${MPI_LIBRARIES})
endif(MPI_FOUND)

if(QUAT_LIBRARY AND VRPN_LIBRARY)
  target_link_libraries(${PROJECT_NAME}
    ${QUAT_LIBRARY}
    ${VRPN_LIBRARY})
endif(QUAT_LIBRARY AND VRPN_LIBRARY)

## #################################################################
## Export header file
## #################################################################

add_compiler_export_flags()

generate_export_header(${PROJECT_NAME}
  EXPORT_FILE_NAME "${PROJECT_NAME}Export.h")

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
  COMMAND ${CMAKE_COMMAND} ARGS -E copy
  "${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}Export.h"
  "${CMAKE_BINARY_DIR}")

## #################################################################
## Handling of generated script modules
## #################################################################

set(${PROJECT_NAME}_MODULES)

if(DTK_BUILD_WRAPPERS AND SWIG_FOUND AND PYTHONLIBS_FOUND)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/dtkVr.i
  COMMAND ${CMAKE_COMMAND} ARGS -E make_directory ${CMAKE_BINARY_DIR}/modules
  COMMAND ${CMAKE_COMMAND} ARGS -E copy ${${PROJECT_NAME}_BINARY_DIR}/vr.py ${CMAKE_BINARY_DIR}/modules
  COMMENT "-- Moving python modules to ${CMAKE_BINARY_DIR}/modules")

set(${PROJECT_NAME}_MODULES ${CMAKE_BINARY_DIR}/modules/vr.py)

endif(DTK_BUILD_WRAPPERS AND SWIG_FOUND AND PYTHONLIBS_FOUND)

## #################################################################
## Source file layout in development environments like Visual Studio
## #################################################################

SOURCE_GROUP("Header Files" REGULAR_EXPRESSION .*\\.h\$)
SOURCE_GROUP("Generated Files" FILES ${${PROJECT_NAME}_SOURCES_MOC})

## #################################################################
## Installation
## #################################################################

string(REGEX REPLACE ".h" ""
     ${PROJECT_NAME}_HEADERS_QTS
  "${${PROJECT_NAME}_HEADERS}")

install(FILES ${${PROJECT_NAME}_HEADERS} DESTINATION include/${PROJECT_NAME})
## #################################################################
## Installation
## #################################################################

foreach(header ${${PROJECT_NAME}_HEADERS})
  string(REGEX REPLACE "(.*)\\.h\$" "\\1" h ${header})
  set(${PROJECT_NAME}_HEADERS_QTS "${${PROJECT_NAME}_HEADERS_QTS}" ${h})
endforeach(header)

set(${PROJECT_NAME}_HEADERS
  ${${PROJECT_NAME}_HEADERS}
 "${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}Export.h")


install(FILES ${${PROJECT_NAME}_HEADERS} DESTINATION include/${PROJECT_NAME})
install(FILES ${${PROJECT_NAME}_HEADERS_QTS} DESTINATION include/${PROJECT_NAME})
install(FILES ${${PROJECT_NAME}_MODULES} DESTINATION modules)
install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)
