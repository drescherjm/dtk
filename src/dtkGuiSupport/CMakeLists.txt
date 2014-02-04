### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Mon Jul 20 22:21:50 2009 (+0200)
## Version: $Id$
## Last-Updated: mar. févr.  4 15:13:32 2014 (+0100)
##           By: Thibaud Kloczko
##     Update #: 325
######################################################################
## 
### Change log:
## 
######################################################################

project(dtkGuiSupport)

## #################################################################
## Sources
## #################################################################

set(${PROJECT_NAME}_HEADERS
  dtkAboutBox.h
  dtkAboutPlugin.h
  dtkAnchoredBar.h
  dtkColorButton.h
  dtkColorGrid.h
  dtkFlowLayout.h
  dtkFinder.h
  dtkObjectEditor.h
  dtkPieChart.h
  dtkPluginsEditor.h
  dtkPopup.h
  dtkProgressIndicator.h
  dtkPropertyEditor.h
  dtkPropertyEditorFactory.h
  dtkRecentFilesMenu.h
  dtkScreenMenu.h
  dtkSearchField.h
  dtkSettingsEditor.h
  dtkSpacer.h
  dtkSplitter.h
  dtkSwitch.h
  dtkTagCloud.h
  dtkToolBox.h
  dtkViewManager.h
  dtkViewLayout.h
  dtkViewLayoutItem.h
  dtkViewList.h
  dtkViewListControl.h)

set(${PROJECT_NAME}_SOURCES
  dtkAboutBox.cpp
  dtkAboutPlugin.cpp
  dtkAnchoredBar.cpp
  dtkColorButton.cpp
  dtkColorGrid.cpp
  dtkFlowLayout.cpp
  dtkFinder.cpp
  dtkObjectEditor.cpp
  dtkPieChart.cpp
  dtkPluginsEditor.cpp
  dtkPopup.cpp
  dtkProgressIndicator.cpp
  dtkPropertyEditor.cpp
  dtkPropertyEditorFactory.cpp
  dtkRecentFilesMenu.cpp
  dtkScreenMenu.cpp
  dtkSettingsEditor.cpp
  dtkSpacer.cpp
  dtkSplitter.cpp
  dtkSwitch.cpp
  dtkTagCloud.cpp
  dtkToolBox.cpp
  dtkViewManager.cpp
  dtkViewLayout.cpp
  dtkViewLayoutItem.cpp
  dtkViewList.cpp
  dtkViewListControl.cpp)

if(APPLE)
set(${PROJECT_NAME}_SOURCES
  ${${PROJECT_NAME}_SOURCES}
    dtkSearchField.mm)
else(APPLE)
set(${PROJECT_NAME}_SOURCES
  ${${PROJECT_NAME}_SOURCES}
    dtkSearchField.cpp)
endif(APPLE)

set(${PROJECT_NAME}_SOURCES_RCC dtkGui.qrc)

## #################################################################
## Build rules
## #################################################################

qt5_wrap_ui(${PROJECT_NAME}_SOURCES_UIC ${${PROJECT_NAME}_FORMS})
qt5_wrap_cpp(${PROJECT_NAME}_SOURCES_MOC ${${PROJECT_NAME}_HEADERS_MOC})
qt5_add_resources(${PROJECT_NAME}_SOURCES_QRC ${${PROJECT_NAME}_SOURCES_RCC})

if(DTK_USE_PRECOMPILED_HEADERS)
  add_precompiled_header(${PROJECT_NAME}_SOURCES_PCH 
    "dtkPch/dtkPch.h" "../dtkPch/dtkPch.cpp" 
    ${${PROJECT_NAME}_SOURCES}
    ${${PROJECT_NAME}_HEADERS}
    ${${PROJECT_NAME}_SOURCES_UIC}
    ${${PROJECT_NAME}_SOURCES_MOC}
    ${${PROJECT_NAME}_SOURCES_QRC})
endif(DTK_USE_PRECOMPILED_HEADERS)

add_library(${PROJECT_NAME}
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_HEADERS}
  ${${PROJECT_NAME}_SOURCES_PCH}
  ${${PROJECT_NAME}_SOURCES_UIC}
  ${${PROJECT_NAME}_SOURCES_MOC}
  ${${PROJECT_NAME}_SOURCES_QRC})

target_link_libraries(${PROJECT_NAME}
  dtkCoreSupport)

if(APPLE)
target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
endif(APPLE)

## ###################################################################
## Link rules
## ###################################################################

qt5_use_modules(${PROJECT_NAME} Core)
qt5_use_modules(${PROJECT_NAME} Gui)
qt5_use_modules(${PROJECT_NAME} Quick)
qt5_use_modules(${PROJECT_NAME} Widgets)

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
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
