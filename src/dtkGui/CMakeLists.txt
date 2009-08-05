### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Mon Jul 20 22:21:50 2009 (+0200)
## Version: $Id$
## Last-Updated: Wed Aug  5 11:15:29 2009 (+0200)
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

project(dtkGui)

## #################################################################
## Sources
## #################################################################

set(${PROJECT_NAME}_HEADERS
  dtkGuiExport.h
  dtkInterpreter.h
  dtkInterpreterPreferencesWidget.h
  dtkSearchBox.h
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
  dtkInterpreter.h
  dtkInterpreterPreferencesWidget.h
  dtkSearchBox.h
  dtkSpacer.h
  dtkSplitter.h
  dtkTagCloud.h
  dtkTextEditor.h
  dtkTextEditorPreferencesWidget.h
  dtkTextEditorSyntaxHighlighter.h
)

set(${PROJECT_NAME}_SOURCES
  dtkInterpreter.cpp
  dtkInterpreterPreferencesWidget.cpp
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
    dtkCocoaUtils.h
    dtkSearchBoxMac.h)
  set(${PROJECT_NAME}_HEADERS_MOC ${${PROJECT_NAME}_HEADERS_MOC}
    dtkSearchBoxMac.h)
  set(${PROJECT_NAME}_SOURCES ${${PROJECT_NAME}_SOURCES}
  dtkCocoaController.mm
  dtkCocoaUtils.mm
  dtkSearchBoxMac.mm)
endif(APPLE)

if(UNIX AND NOT APPLE)
  set(${PROJECT_NAME}_HEADERS ${${PROJECT_NAME}_HEADERS}
    dtkSearchBoxUnix.h)
  set(${PROJECT_NAME}_HEADERS_MOC ${${PROJECT_NAME}_HEADERS_MOC}
    dtkSearchBoxUnix.h)
  set(${PROJECT_NAME}_SOURCES ${${PROJECT_NAME}_SOURCES}
  dtkSearchBoxUnix.cpp)
endif(UNIX AND NOT APPLE)

if(WIN32)
  set(${PROJECT_NAME}_HEADERS ${${PROJECT_NAME}_HEADERS}
    dtkSearchBoxUnix.h)
  set(${PROJECT_NAME}_HEADERS_MOC ${${PROJECT_NAME}_HEADERS_MOC}
    dtkSearchBoxUnix.h)
  set(${PROJECT_NAME}_SOURCES ${${PROJECT_NAME}_SOURCES}
  dtkSearchBoxUnix.cpp)
endif(WIN32)

set(${PROJECT_NAME}_FORMS
  dtkInterpreterPreferencesWidget.ui
  dtkTextEditorPreferencesWidget.ui
)

## #################################################################
## Build rules
## #################################################################

qt4_wrap_ui(${PROJECT_NAME}_SOURCES_UIC ${${PROJECT_NAME}_FORMS})

qt4_wrap_cpp(${PROJECT_NAME}_SOURCES_MOC ${${PROJECT_NAME}_HEADERS_MOC})

add_library(${PROJECT_NAME}
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
