### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Wed Jan 13 13:57:41 2010 (+0100)
## Version: $Id$
## Last-Updated: Thu Sep 27 15:24:49 2012 (+0200)
##           By: Julien Wintz
##     Update #: 336
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

project(dtkVrSupport)

## #################################################################
## Sources
## #################################################################

set(${PROJECT_NAME}_HEADERS
  dtkVrFlystickRecognizer.h
  dtkVrGestureRecognizer.h
  dtkVrHeadRecognizer.h
  dtkVrScreen.h
  dtkVrTracker.h)

set(${PROJECT_NAME}_SOURCES
  dtkVrFlystickRecognizer.cpp
  dtkVrGestureRecognizer.cpp
  dtkVrHeadRecognizer.cpp
  dtkVrScreen.cpp
  dtkVrTracker.cpp)


## #################################################################
## Vrpn sources
## #################################################################

if(DTK_HAVE_VRPN)

set(${PROJECT_NAME}_HEADERS ${${PROJECT_NAME}_HEADERS}
  dtkVrTrackerVrpn.h)

set(${PROJECT_NAME}_SOURCES ${${PROJECT_NAME}_SOURCES}
  dtkVrTrackerVrpn.cpp)

endif(DTK_HAVE_VRPN)

## #################################################################
## Kinect sources
## #################################################################

if(DTK_HAVE_NITE)

set(${PROJECT_NAME}_HEADERS ${${PROJECT_NAME}_HEADERS}
  dtkVrTrackerKinect.h)

set(${PROJECT_NAME}_SOURCES ${${PROJECT_NAME}_SOURCES}
  dtkVrTrackerKinect.cpp
  dtkVrTrackerKinect_p.cpp)

set(DTKVRTRACKERKINECT_XML_PATH "${PROJECT_SOURCE_DIR}/dtkVrTrackerKinectConfig.xml")

configure_file(
  "${PROJECT_SOURCE_DIR}/dtkVrTrackerKinectConfig.h.in"
  "${CMAKE_BINARY_DIR}/dtkVrTrackerKinectConfig.h")

endif(DTK_HAVE_NITE)

## #################################################################
## Build rules
## #################################################################


add_library(${PROJECT_NAME} SHARED
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_HEADERS}
)

target_link_libraries(${PROJECT_NAME}
  dtkMathSupport
  dtkCoreSupport
  dtkLog)

if(MSVC)
  target_link_libraries(${PROJECT_NAME} wsock32)
endif(MSVC)

if(QUAT_LIBRARY AND VRPN_LIBRARY)
  target_link_libraries(${PROJECT_NAME}
    ${QUAT_LIBRARY}
    ${VRPN_LIBRARY})
endif(QUAT_LIBRARY AND VRPN_LIBRARY)

if(DTK_HAVE_NITE)
  target_link_libraries(${PROJECT_NAME}
  OpenNI
  XnVNite
  XnVCNite)
endif(DTK_HAVE_NITE)

## #################################################################
## Target properties
## #################################################################

set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_RPATH 0)
set_target_properties(${PROJECT_NAME} PROPERTIES INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
set_target_properties(${PROJECT_NAME} PROPERTIES INSTALL_RPATH    "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")

## #################################################################
## Export header file
## #################################################################

add_compiler_export_flags()

generate_export_header(${PROJECT_NAME}
  EXPORT_FILE_NAME "${PROJECT_NAME}Export.h")

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
  COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different "${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}Export.h" "${CMAKE_BINARY_DIR}"
  COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different "${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}Export.h" "${CMAKE_BINARY_DIR}/${PROJECT_NAME}Export")

set(${PROJECT_NAME}_HEADERS
  ${${PROJECT_NAME}_HEADERS}
 "${CMAKE_BINARY_DIR}/${PROJECT_NAME}Export.h")

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
  DESTINATION ${CMAKE_INSTALL_LIBDIR}
  COMPONENT vrsupport
  EXPORT dtkDepends
  )
