### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Mon Aug  3 17:34:51 2009 (+0200)
## Version: $Id$
## Last-Updated: Mon Jan 25 12:33:16 2010 (+0100)
##           By: Julien Wintz
##     Update #: 68
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

set(${PROJECT_NAME}_HEADERS

)

set(${PROJECT_NAME}_HEADERS_MOC
  dtkCreatorMainWindow.h
  dtkCreatorPluginBrowser.h
  dtkCreatorScriptBrowser.h
  dtkCreatorViewer.h
  dtkCreatorWidgetFactory.h
)

set(${PROJECT_NAME}_SOURCES
  dtkCreatorController.cpp
  dtkCreatorMainWindow.cpp
  dtkCreatorPluginBrowser.cpp
  dtkCreatorScriptBrowser.cpp
  dtkCreatorViewer.cpp
  dtkCreatorWidgetFactory.cpp
  main.cpp
)

set(${PROJECT_NAME}_RESOURCES
  icons/icons.qrc
)

## #################################################################
## Wrapping
## #################################################################

set(${PROJECT_NAME}_WRAP_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/dtkCreatorViewer.h)

dtk_wrap(${PROJECT_NAME} ${PROJECT_NAME}_SOURCES_WRAP creator python ${CMAKE_CURRENT_SOURCE_DIR}/dtkCreator.i ${${PROJECT_NAME}_WRAP_DEPENDS})
dtk_wrap(${PROJECT_NAME} ${PROJECT_NAME}_SOURCES_WRAP creator tcl    ${CMAKE_CURRENT_SOURCE_DIR}/dtkCreator.i ${${PROJECT_NAME}_WRAP_DEPENDS})

## #################################################################
## Build rules
## #################################################################

add_definitions(-Wno-write-strings)
add_definitions(-Wformat=0)

qt4_wrap_cpp(${PROJECT_NAME}_SOURCES_MOC ${${PROJECT_NAME}_HEADERS_MOC})

qt4_add_RESOURCES(${PROJECT_NAME}_SOURCES_QRC ${${PROJECT_NAME}_RESOURCES})

add_executable(${PROJECT_NAME} MACOSX_BUNDLE
  ${${PROJECT_NAME}_SOURCES_WRAP}
  ${${PROJECT_NAME}_SOURCES_QRC}
  ${${PROJECT_NAME}_SOURCES_MOC}
  ${${PROJECT_NAME}_SOURCES}
)

target_link_libraries(${PROJECT_NAME}
  ${QT_LIBRARIES}
  dtkCore
  dtkScript
  dtkGui
  dtkComposer
  dtkCrypto
  dtkVr
)

## #################################################################
## Handling of generated script modules
## #################################################################

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/dtkCreator.i
  COMMAND ${CMAKE_COMMAND} ARGS -E  make_directory ${CMAKE_BINARY_DIR}/modules
  COMMAND ${CMAKE_COMMAND} ARGS -E  copy ${${PROJECT_NAME}_BINARY_DIR}/creator.py ${CMAKE_BINARY_DIR}/modules
  COMMENT "-- Moving python modules to ${CMAKE_BINARY_DIR}/modules"
)

## #################################################################
## Bundle setup
## #################################################################

if(APPLE)
  set(MACOSX_BUNDLE_ICON_FILE ${PROJECT_NAME}.icns)
  SET(MACOSX_BUNDLE_SHORT_VERSION_STRING 0.1.0)
  SET(MACOSX_BUNDLE_VERSION 0.1.0)
  SET(MACOSX_BUNDLE_LONG_VERSION_STRING Version 0.1.0)
  set(${PROJECT_NAME}_RESOURCE_DIR ${EXECUTABLE_OUTPUT_PATH}/${PROJECT_NAME}.app/Contents/Resources)
# set(${PROJECT_NAME}_PLUGINS_DIR  ${EXECUTABLE_OUTPUT_PATH}/${PROJECT_NAME}.app/Contents/Plugins)
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} ARGS -E make_directory ${${PROJECT_NAME}_RESOURCE_DIR}
#   COMMAND ${CMAKE_COMMAND} ARGS -E make_directory ${${PROJECT_NAME}_PLUGINS_DIR}
    COMMAND ${CMAKE_COMMAND} ARGS -E copy ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.icns ${${PROJECT_NAME}_RESOURCE_DIR}
    COMMENT "-- Setting up plugins and resources")
endif(APPLE)

## #################################################################
## Installation
## #################################################################

if(NOT dtk_INSTALL_NO_RUNTIME)
  install_targets(${dtk_INSTALL_BIN_DIR} ${PROJECT_NAME})
  install_files(${dtk_INSTALL_MODULE_DIR} .py ${CMAKE_BINARY_DIR}/modules/creator.py)
endif(NOT dtk_INSTALL_NO_RUNTIME)
