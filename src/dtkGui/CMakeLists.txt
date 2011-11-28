### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Mon Jul 20 22:21:50 2009 (+0200)
## Version: $Id$
## Last-Updated: Thu Nov 17 10:16:46 2011 (+0100)
##           By: Julien Wintz
##     Update #: 206
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
  dtkAboutPlugin.h
  dtkAddressBar.h
  dtkAnchoredBar.h
  dtkColorButton.h
  dtkColorGrid.h
  dtkFinder.h
  dtkGuiExport.h
  dtkInsetMenu.h
  dtkInspector.h
  dtkInspectorBox.h
  dtkInspectorButton.h
  dtkInspectorTitleBar.h
  dtkInspectorToolBar.h
  dtkInspectorSwitch.h
  dtkInterpreter.h
  dtkInterpreterPreferencesWidget.h
  dtkNavigationBar.h
  dtkPluginsEditor.h
  dtkPopup.h
  dtkPreferencesWidget.h
  dtkProgressIndicator.h
  dtkRecentFilesMenu.h
  dtkRegistrationBar.h
  dtkSearchBar.h
  dtkSettingsEditor.h
  dtkSettingsEditorPreferencesWidget.h
  dtkSpacer.h
  dtkSplitter.h
  dtkTextEditor.h
  dtkTextEditorPreferencesWidget.h
  dtkTextEditorSyntaxHighlighter.h
  dtkTextEditorSyntaxHighlighterCpp.h
  dtkTextEditorSyntaxHighlighterPython.h
  dtkTextEditorSyntaxHighlighterTcl.h)

if(QT_QTWEBKIT_FOUND)
set(${PROJECT_NAME}_HEADERS
  ${${PROJECT_NAME}_HEADERS}
  dtkTagCloud.h)
endif(QT_QTWEBKIT_FOUND)

set(${PROJECT_NAME}_HEADERS_MOC
  dtkAboutBox.h
  dtkAboutPlugin.h
  dtkAddressBar.h
  dtkAnchoredBar.h
  dtkColorButton.h
  dtkColorGrid.h
  dtkFinder.h
  dtkInsetMenu.h
  dtkInspector.h
  dtkInspectorBox.h
  dtkInspectorButton.h
  dtkInspectorTitleBar.h
  dtkInspectorToolBar.h
  dtkInspectorSwitch.h
  dtkInterpreter.h
  dtkInterpreterPreferencesWidget.h
  dtkNavigationBar.h
  dtkPluginsEditor.h
  dtkPopup.h
  dtkPreferencesWidget.h
  dtkProgressIndicator.h
  dtkRecentFilesMenu.h
  dtkRegistrationBar.h
  dtkSearchBar.h
  dtkSettingsEditor.h
  dtkSettingsEditorPreferencesWidget.h
  dtkSpacer.h
  dtkSplitter.h
  dtkTextEditor.h
  dtkTextEditorPreferencesWidget.h
  dtkTextEditorSyntaxHighlighter.h)

if(QT_QTWEBKIT_FOUND)
set(${PROJECT_NAME}_HEADERS_MOC
  ${${PROJECT_NAME}_HEADERS_MOC}
  dtkTagCloud.h)
endif(QT_QTWEBKIT_FOUND)

set(${PROJECT_NAME}_SOURCES
  dtkAboutBox.cpp
  dtkAboutPlugin.cpp
  dtkAddressBar.cpp
  dtkAnchoredBar.cpp
  dtkColorButton.cpp
  dtkColorGrid.cpp
  dtkFinder.cpp
  dtkInsetMenu.cpp
  dtkInspector.cpp
  dtkInspectorBox.cpp
  dtkInspectorButton.cpp
  dtkInspectorTitleBar.cpp
  dtkInspectorToolBar.cpp
  dtkInspectorSwitch.cpp
  dtkInterpreter.cpp
  dtkInterpreterPreferencesWidget.cpp
  dtkNavigationBar.cpp
  dtkPluginsEditor.cpp
  dtkPopup.cpp
  dtkPreferencesWidget.cpp
  dtkProgressIndicator.cpp
  dtkRecentFilesMenu.cpp
  dtkRegistrationBar.cpp
  dtkSearchBar.cpp
  dtkSettingsEditor.cpp
  dtkSettingsEditorPreferencesWidget.cpp
  dtkSpacer.cpp
  dtkSplitter.cpp
  dtkTextEditor.cpp
  dtkTextEditorPreferencesWidget.cpp
  dtkTextEditorSyntaxHighlighter.cpp
  dtkTextEditorSyntaxHighlighterCpp.cpp
  dtkTextEditorSyntaxHighlighterPython.cpp
  dtkTextEditorSyntaxHighlighterTcl.cpp)

if(QT_QTWEBKIT_FOUND)
set(${PROJECT_NAME}_SOURCES
  ${${PROJECT_NAME}_SOURCES}
  dtkTagCloud.cpp)
endif(QT_QTWEBKIT_FOUND)

set(${PROJECT_NAME}_FORMS
  dtkInterpreterPreferencesWidget.ui
  dtkTextEditorPreferencesWidget.ui)

set(${PROJECT_NAME}_RESOURCES dtkGui.qrc)

## #################################################################
## Build rules
## #################################################################

add_definitions(${QT_DEFINITIONS})
add_definitions(-DQT_SHARED)
if(NOT MSVC)
  add_definitions(-DQT_NO_DEBUG)
endif(NOT MSVC)

qt4_wrap_ui(${PROJECT_NAME}_SOURCES_UIC ${${PROJECT_NAME}_FORMS})
qt4_wrap_cpp(${PROJECT_NAME}_SOURCES_MOC ${${PROJECT_NAME}_HEADERS_MOC})
qt4_add_RESOURCES(${PROJECT_NAME}_SOURCES_QRC ${${PROJECT_NAME}_RESOURCES})

if(DTK_USE_PRECOMPILED_HEADERS)
  add_precompiled_header(${PROJECT_NAME}_SOURCES_PCH 
    "dtkPch/dtkPch.h" "../dtkPch/dtkPch.cpp" 
    ${${PROJECT_NAME}_SOURCES}
    ${${PROJECT_NAME}_HEADERS}
    ${${PROJECT_NAME}_SOURCES_UIC}
    ${${PROJECT_NAME}_SOURCES_MOC}
    ${${PROJECT_NAME}_SOURCES_QRC})
endif(DTK_USE_PRECOMPILED_HEADERS)

if(BUILD_SHARED_LIBS)

add_library(${PROJECT_NAME} SHARED
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_HEADERS}
  ${${PROJECT_NAME}_SOURCES_PCH}
  ${${PROJECT_NAME}_SOURCES_UIC}
  ${${PROJECT_NAME}_SOURCES_MOC}
  ${${PROJECT_NAME}_SOURCES_QRC})

else(BUILD_SHARED_LIBS)

add_library(${PROJECT_NAME} STATIC
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_HEADERS}
  ${${PROJECT_NAME}_SOURCES_PCH}
  ${${PROJECT_NAME}_SOURCES_UIC}
  ${${PROJECT_NAME}_SOURCES_MOC}
  ${${PROJECT_NAME}_SOURCES_QRC})

endif(BUILD_SHARED_LIBS)

target_link_libraries(${PROJECT_NAME}
  ${QT_LIBRARIES}
  dtkCore
  dtkScript)

## #################################################################
## Source file layout in development environments like Visual Studio
## #################################################################

SOURCE_GROUP("Header Files" REGULAR_EXPRESSION .*\\.h\$)
SOURCE_GROUP("Generated Files" FILES ${${PROJECT_NAME}_SOURCES_UIC} ${${PROJECT_NAME}_SOURCES_MOC} ${${PROJECT_NAME}_SOURCES_QRC})

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
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)
