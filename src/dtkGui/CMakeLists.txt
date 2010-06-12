### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Mon Jul 20 22:21:50 2009 (+0200)
## Version: $Id$
## Last-Updated: Sat Jun 12 15:51:21 2010 (+0200)
##           By: Julien Wintz
##     Update #: 143
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
  dtkAboutBox.h
  dtkAddressBar.h
  dtkAnchoredBar.h
  dtkFinder.h
  dtkGuiExport.h
  dtkInsetMenu.h
  dtkInspector.h
  dtkInspectorComposer.h
  dtkInspectorScene.h
  dtkInterpreter.h
  dtkInterpreterPreferencesWidget.h
  dtkNavigationBar.h
  dtkPreferencesWidget.h
  dtkProgressIndicator.h
  dtkRecentFilesMenu.h
  dtkRegistrationBar.h
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
  dtkTextEditorSyntaxHighlighterTcl.h)

set(${PROJECT_NAME}_HEADERS_MOC
  dtkAboutBox.h
  dtkAddressBar.h
  dtkAnchoredBar.h
  dtkFinder.h
  dtkInsetMenu.h
  dtkInspector.h
  dtkInspectorComposer.h
  dtkInspectorScene.h
  dtkInterpreter.h
  dtkInterpreterPreferencesWidget.h
  dtkNavigationBar.h
  dtkPreferencesWidget.h
  dtkProgressIndicator.h
  dtkRecentFilesMenu.h
  dtkRegistrationBar.h
  dtkSearchBar.h
  dtkSettingsEditor.h
  dtkSettingsEditorPreferencesWidget.h
  dtkSpacer.h
  dtkSplitter.h
  dtkTagCloud.h
  dtkTextEditor.h
  dtkTextEditorPreferencesWidget.h
  dtkTextEditorSyntaxHighlighter.h)

set(${PROJECT_NAME}_SOURCES
  dtkAboutBox.cpp
  dtkAddressBar.cpp
  dtkAnchoredBar.cpp
  dtkFinder.cpp
  dtkInsetMenu.cpp
  dtkInspector.cpp
  dtkInspectorComposer.cpp
  dtkInspectorScene.cpp
  dtkInterpreter.cpp
  dtkInterpreterPreferencesWidget.cpp
  dtkNavigationBar.cpp
  dtkPreferencesWidget.cpp
  dtkProgressIndicator.cpp
  dtkRecentFilesMenu.cpp
  dtkRegistrationBar.cpp
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
  dtkTextEditorSyntaxHighlighterTcl.cpp)

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
  dtkTextEditorPreferencesWidget.ui)

set(${PROJECT_NAME}_RESOURCES dtkGui.qrc)

## #################################################################
## Build rules
## #################################################################

add_definitions(${QT_DEFINITIONS})
add_definitions(-DQT_SHARED)
add_definitions(-DQT_NO_DEBUG)

qt4_wrap_ui(${PROJECT_NAME}_SOURCES_UIC ${${PROJECT_NAME}_FORMS})
qt4_wrap_cpp(${PROJECT_NAME}_SOURCES_MOC ${${PROJECT_NAME}_HEADERS_MOC})
qt4_add_RESOURCES(${PROJECT_NAME}_SOURCES_QRC ${${PROJECT_NAME}_RESOURCES})

add_library(${PROJECT_NAME} SHARED
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_SOURCES_UIC}
  ${${PROJECT_NAME}_SOURCES_MOC}
  ${${PROJECT_NAME}_SOURCES_QRC})

target_link_libraries(${PROJECT_NAME}
  ${QT_LIBRARIES}
  dtkCore
  dtkScript)

if(APPLE)
target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
endif(APPLE)

## #################################################################
## Installation
## #################################################################

install(FILES ${${PROJECT_NAME}_HEADERS} DESTINATION include/${PROJECT_NAME})
install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)

