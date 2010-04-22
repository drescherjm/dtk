### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Mon Aug  3 17:34:51 2009 (+0200)
## Version: $Id$
## Last-Updated: Thu Apr 22 14:59:32 2010 (+0200)
##           By: Julien Wintz
##     Update #: 111
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

project(dtkCreator)

## #################################################################
## Sources
## #################################################################

set(${PROJECT_NAME}_HEADERS_MOC
  dtkCreatorMainWindow.h
  dtkCreatorPluginBrowser.h
  dtkCreatorScriptBrowser.h
  dtkCreatorViewer.h
  dtkCreatorWidgetFactory.h)

set(${PROJECT_NAME}_SOURCES
  dtkCreatorController.cpp
  dtkCreatorMainWindow.cpp
  dtkCreatorPluginBrowser.cpp
  dtkCreatorScriptBrowser.cpp
  dtkCreatorViewer.cpp
  dtkCreatorWidgetFactory.cpp
  main.cpp)

## #################################################################
## Wrapping
## #################################################################

set(${PROJECT_NAME}_WRAP_DEPENDS ${${PROJECT_NAME}_HEADERS_MOC})

dtk_wrap(${PROJECT_NAME} ${PROJECT_NAME}_SOURCES_WRAP creator python ${CMAKE_CURRENT_SOURCE_DIR}/dtkCreator.i ${${PROJECT_NAME}_WRAP_DEPENDS})
dtk_wrap(${PROJECT_NAME} ${PROJECT_NAME}_SOURCES_WRAP creator tcl    ${CMAKE_CURRENT_SOURCE_DIR}/dtkCreator.i ${${PROJECT_NAME}_WRAP_DEPENDS})

## #################################################################
## Build rules
## #################################################################

if(NOT MSVC)
add_definitions(-Wno-write-strings)
add_definitions(-Wformat=0)
endif(NOT MSVC)

qt4_wrap_cpp(${PROJECT_NAME}_SOURCES_MOC ${${PROJECT_NAME}_HEADERS_MOC})

add_executable(${PROJECT_NAME} MACOSX_BUNDLE WIN32
  ${${PROJECT_NAME}_SOURCES_WRAP}
  ${${PROJECT_NAME}_SOURCES_MOC}
  ${${PROJECT_NAME}_SOURCES})

target_link_libraries(${PROJECT_NAME}
  ${QT_LIBRARIES}
  dtkCore
  dtkScript
  dtkGui
  dtkComposer
  dtkDistributed
  dtkVr)

## #################################################################
## Handling of generated script modules
## #################################################################

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/dtkCreator.i
  COMMAND ${CMAKE_COMMAND} ARGS -E  make_directory ${CMAKE_BINARY_DIR}/modules
  COMMAND ${CMAKE_COMMAND} ARGS -E  copy ${${PROJECT_NAME}_BINARY_DIR}/creator.py ${CMAKE_BINARY_DIR}/modules
  COMMENT "-- Moving python modules to ${CMAKE_BINARY_DIR}/modules"
)

set(${PROJECT_NAME}_MODULES ${CMAKE_BINARY_DIR}/modules/creator.py)

## #################################################################
## Bundle setup
## #################################################################

if(APPLE)
  set(MACOSX_BUNDLE_ICON_FILE ${PROJECT_NAME}.icns)
  SET(MACOSX_BUNDLE_SHORT_VERSION_STRING 0.1.0)
  SET(MACOSX_BUNDLE_VERSION 0.1.0)
  SET(MACOSX_BUNDLE_LONG_VERSION_STRING Version 0.1.0)
  set(${PROJECT_NAME}_RESOURCE_DIR ${EXECUTABLE_OUTPUT_PATH}/${PROJECT_NAME}.app/Contents/Resources)
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} ARGS -E make_directory ${${PROJECT_NAME}_RESOURCE_DIR}
    COMMAND ${CMAKE_COMMAND} ARGS -E copy ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.icns ${${PROJECT_NAME}_RESOURCE_DIR}
    COMMENT "-- Setting up resources")
endif(APPLE)

## #################################################################
## Installation
## #################################################################

install(FILES ${${PROJECT_NAME}_MODULES} DESTINATION modules)
install(TARGETS ${PROJECT_NAME}
   BUNDLE DESTINATION bin
  RUNTIME DESTINATION bin)

install(CODE "
  set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} \"${CMAKE_SOURCE_DIR}/cmake\")
  include(dtkInstall)
  dtk_post_install(${PROJECT_NAME})"
)
