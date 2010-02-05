### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Mon Jul 20 22:21:50 2009 (+0200)
## Version: $Id$
## Last-Updated: Thu Feb  4 18:32:34 2010 (+0100)
##           By: Julien Wintz
##     Update #: 96
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

project(dtkGui)

## #################################################################
## Sources
## #################################################################

set(${PROJECT_NAME}_HEADERS
  dtkAddressBar.h
  dtkGuiExport.h
  dtkInspector.h
  dtkInspectorComposer.h
  dtkInspectorScene.h
  dtkInterpreter.h
  dtkInterpreterPreferencesWidget.h
  dtkNavigationBar.h
  dtkPreferencesWidget.h
  dtkSearchBar.h
  dtkSettingsEditor.h
  dtkSettingsEditorPreferencesWidget.h
  dtkSpacer.h
  dtkSplitter.h
  dtkTagCloud.h
  dtkTextEditor.h
  dtkTextEditorPreferencesWidget.h
  dtkTextEditorSyntaxHighlighter.h
  dtkTextEditorSyntaxHighlighterCpp.h
  dtkTextEditorSyntaxHighlighterPython.h
  dtkTextEditorSyntaxHighlighterTcl.h
)

set(${PROJECT_NAME}_HEADERS_MOC
  dtkAddressBar.h
  dtkInspector.h
  dtkInspectorComposer.h
  dtkInspectorScene.h
  dtkInterpreter.h
  dtkInterpreterPreferencesWidget.h
  dtkNavigationBar.h
  dtkPreferencesWidget.h
  dtkSearchBar.h
  dtkSettingsEditor.h
  dtkSettingsEditorPreferencesWidget.h
  dtkSpacer.h
  dtkSplitter.h
  dtkTagCloud.h
  dtkTextEditor.h
  dtkTextEditorPreferencesWidget.h
  dtkTextEditorSyntaxHighlighter.h
)

set(${PROJECT_NAME}_SOURCES
  dtkAddressBar.cpp
  dtkInspector.cpp
  dtkInspectorComposer.cpp
  dtkInspectorScene.cpp
  dtkInterpreter.cpp
  dtkInterpreterPreferencesWidget.cpp
  dtkNavigationBar.cpp
  dtkPreferencesWidget.cpp
  dtkSearchBar.cpp
  dtkSettingsEditor.cpp
  dtkSettingsEditorPreferencesWidget.cpp
  dtkSpacer.cpp
  dtkSplitter.cpp
  dtkTagCloud.cpp
  dtkTextEditor.cpp
  dtkTextEditorPreferencesWidget.cpp
  dtkTextEditorSyntaxHighlighter.cpp
  dtkTextEditorSyntaxHighlighterCpp.cpp
  dtkTextEditorSyntaxHighlighterPython.cpp
  dtkTextEditorSyntaxHighlighterTcl.cpp
)

if(APPLE)
  set(${PROJECT_NAME}_HEADERS ${${PROJECT_NAME}_HEADERS}
    dtkCocoaController.h
    dtkCocoaUtils.h)
  set(${PROJECT_NAME}_SOURCES ${${PROJECT_NAME}_SOURCES}
  dtkCocoaController.mm
  dtkCocoaUtils.mm)
endif(APPLE)

set(${PROJECT_NAME}_FORMS
  dtkInterpreterPreferencesWidget.ui
  dtkTextEditorPreferencesWidget.ui
)

## #################################################################
## Build rules
## #################################################################

add_definitions(${QT_DEFINITIONS})
add_definitions(-DQT_SHARED)
add_definitions(-DQT_NO_DEBUG)

qt4_wrap_ui(${PROJECT_NAME}_SOURCES_UIC ${${PROJECT_NAME}_FORMS})

qt4_wrap_cpp(${PROJECT_NAME}_SOURCES_MOC ${${PROJECT_NAME}_HEADERS_MOC})

add_library(${PROJECT_NAME} SHARED
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_SOURCES_UIC}
  ${${PROJECT_NAME}_SOURCES_MOC}
)

target_link_libraries(${PROJECT_NAME}
  ${QT_LIBRARIES}
  dtkCore
  dtkScript
)

## #################################################################
## Installation
## #################################################################

if(NOT dtk_INSTALL_NO_DEVELOPMENT)
  install_files(${dtk_INSTALL_INCLUDE_DIR}/${PROJECT_NAME} .h ${${PROJECT_NAME}_HEADERS})
endif(NOT dtk_INSTALL_NO_DEVELOPMENT)

if(NOT dtk_INSTALL_NO_LIBRARIES)
  install_targets(${dtk_INSTALL_LIB_DIR} RUNTIME_DIRECTORY ${dtk_INSTALL_BIN_DIR} ${PROJECT_NAME})
endif(NOT dtk_INSTALL_NO_LIBRARIES)
