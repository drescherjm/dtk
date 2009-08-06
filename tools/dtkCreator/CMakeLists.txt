### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Mon Aug  3 17:34:51 2009 (+0200)
## Version: $Id$
## Last-Updated: Thu Aug  6 18:07:33 2009 (+0200)
##           By: Julien Wintz
##     Update #: 34
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
