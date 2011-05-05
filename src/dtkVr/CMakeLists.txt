### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Wed Jan 13 13:57:41 2010 (+0100)
## Version: $Id$
## Last-Updated: Fri Apr 29 12:27:59 2011 (+0200)
##           By: Julien Wintz
##     Update #: 276
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
  dtkVrExport.h
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

if(BUILD_WRAPPERS AND SWIG_FOUND)

  set(${PROJECT_NAME}_WRAP_DEPENDS ${${PROJECT_NAME}_HEADERS})
  
  if(PYTHONLIBS_FOUND)
    dtk_wrap(${PROJECT_NAME} ${PROJECT_NAME}_SOURCES_WRAP vr python ${CMAKE_CURRENT_SOURCE_DIR}/dtkVr.i ${${PROJECT_NAME}_WRAP_DEPENDS})
  endif(PYTHONLIBS_FOUND)

  if(TCL_FOUND)
    dtk_wrap(${PROJECT_NAME} ${PROJECT_NAME}_SOURCES_WRAP vr tcl    ${CMAKE_CURRENT_SOURCE_DIR}/dtkVr.i ${${PROJECT_NAME}_WRAP_DEPENDS})
  endif(TCL_FOUND)

endif(BUILD_WRAPPERS AND SWIG_FOUND)

## #################################################################
## Build rules
## #################################################################

if(NOT WIN32)
add_definitions(-Wno-write-strings)
add_definitions(-Wformat=0)
endif(NOT WIN32)

add_definitions(${QT_DEFINITIONS})
add_definitions(-DQT_SHARED)
if(NOT MSVC)
  # Shouldn't the QT_USE_FILE set this appropriately?
  add_definitions(-DQT_NO_DEBUG)
endif(NOT MSVC)

qt4_wrap_cpp(${PROJECT_NAME}_SOURCES_MOC ${${PROJECT_NAME}_HEADERS_MOC})

add_library(${PROJECT_NAME} SHARED
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_HEADERS}
  ${${PROJECT_NAME}_SOURCES_MOC}
  ${${PROJECT_NAME}_SOURCES_WRAP})

target_link_libraries(${PROJECT_NAME}
  dtkMath
  dtkCore
  dtkDistributed)

if(MSVC)
  target_link_libraries(${PROJECT_NAME}
    wsock32)
endif()

if(MPI_FOUND)
target_link_libraries(${PROJECT_NAME}
  ${MPI_LIBRARIES})
endif(MPI_FOUND)

if(QUAT_LIBRARIES AND VRPN_LIBRARIES)
target_link_libraries(${PROJECT_NAME}
  ${QUAT_LIBRARIES}
  ${VRPN_LIBRARIES})
endif(QUAT_LIBRARIES AND VRPN_LIBRARIES)

## #################################################################
## Handling of generated script modules
## #################################################################

set(${PROJECT_NAME}_MODULES)

if(BUILD_WRAPPERS AND SWIG_FOUND AND PYTHONLIBS_FOUND)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/dtkVr.i
  COMMAND ${CMAKE_COMMAND} ARGS -E  make_directory ${CMAKE_BINARY_DIR}/modules
  COMMAND ${CMAKE_COMMAND} ARGS -E  copy ${${PROJECT_NAME}_BINARY_DIR}/vr.py ${CMAKE_BINARY_DIR}/modules
  COMMENT "-- Moving python modules to ${CMAKE_BINARY_DIR}/modules"
)

set(${PROJECT_NAME}_MODULES ${CMAKE_BINARY_DIR}/modules/vr.py)

endif(BUILD_WRAPPERS AND SWIG_FOUND AND PYTHONLIBS_FOUND)

## #################################################################
## Source file layout in development environments like Visual Studio
## #################################################################

SOURCE_GROUP("Header Files" REGULAR_EXPRESSION .*\\.h\$)
SOURCE_GROUP("Generated Files" FILES ${${PROJECT_NAME}_SOURCES_MOC})

## #################################################################
## Installation
## #################################################################

install(FILES ${${PROJECT_NAME}_HEADERS} DESTINATION include/${PROJECT_NAME})
install(FILES ${${PROJECT_NAME}_MODULES} DESTINATION modules)
install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)

