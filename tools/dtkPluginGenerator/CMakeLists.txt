### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Mon Mar  9 21:07:07 2009 (+0100)
## Version: $Id$
## Last-Updated: Tue Apr  6 09:28:12 2010 (+0200)
##           By: Julien Wintz
##     Update #: 48
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

project(dtkPluginGenerator)

## #################################################################
## Sources
## #################################################################

set(${PROJECT_NAME}_HEADERS_MOC
  dtkPluginGeneratorMainWindow.h)

set(${PROJECT_NAME}_SOURCES
  dtkPluginGenerator.cpp
  dtkPluginGeneratorMainWindow.cpp
  anyoption.cpp
  main.cpp)

set(${PROJECT_NAME}_FORMS
  dtkPluginGeneratorMainWindow.ui)

set(${PROJECT_NAME}_RESOURCES
  template/template.qrc)

## #################################################################
## Build rules
## #################################################################

qt4_wrap_ui(${PROJECT_NAME}_SOURCES_UIC ${${PROJECT_NAME}_FORMS})
qt4_wrap_cpp(${PROJECT_NAME}_SOURCES_MOC ${${PROJECT_NAME}_HEADERS_MOC})
qt4_add_RESOURCES(${PROJECT_NAME}_SOURCES_QRC ${${PROJECT_NAME}_RESOURCES})

add_executable(${PROJECT_NAME} MACOSX_BUNDLE
  ${${PROJECT_NAME}_SOURCES_UIC}
  ${${PROJECT_NAME}_SOURCES_MOC}
  ${${PROJECT_NAME}_SOURCES_QRC}
  ${${PROJECT_NAME}_SOURCES})

target_link_libraries(${PROJECT_NAME}
  ${QT_LIBRARIES})

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
    COMMENT "-- Setting up plugins and resources")
endif(APPLE)

## #################################################################
## Installation
## #################################################################

install(TARGETS ${PROJECT_NAME}
   BUNDLE DESTINATION bin
  RUNTIME DESTINATION bin)
