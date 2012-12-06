### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Mon Jul 20 22:21:50 2009 (+0200)
## Version: $Id$
## Last-Updated: Thu Dec  6 14:25:08 2012 (+0100)
##           By: Julien Wintz
##     Update #: 269
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
  dtkAnchoredBar.h
  dtkColorButton.h
  dtkColorGrid.h
  dtkFlowLayout.h
  dtkFinder.h
  dtkPieChart.h
  dtkPluginsEditor.h
  dtkPopup.h
  dtkProgressIndicator.h
  dtkRecentFilesMenu.h
  dtkSearchField.h
  dtkSettingsEditor.h
  dtkSpacer.h
  dtkSplitter.h
  dtkSwitch.h
  dtkTagCloud.h
  dtkTextEditor.h
  dtkViewManager.h
  dtkViewLayout.h
  dtkViewLayoutItem.h
  dtkViewList.h
  dtkViewListControl.h)

set(${PROJECT_NAME}_HEADERS_MOC
  dtkAboutBox.h
  dtkAboutPlugin.h
  dtkAnchoredBar.h
  dtkColorButton.h
  dtkColorGrid.h
  dtkFinder.h
  dtkPieChart.h
  dtkPluginsEditor.h
  dtkPopup.h
  dtkProgressIndicator.h
  dtkRecentFilesMenu.h
  dtkSearchField.h
  dtkSettingsEditor.h
  dtkSpacer.h
  dtkSplitter.h
  dtkTagCloud.h
  dtkSwitch.h
  dtkTextEditor.h
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
  dtkPieChart.cpp
  dtkPluginsEditor.cpp
  dtkPopup.cpp
  dtkProgressIndicator.cpp
  dtkRecentFilesMenu.cpp
  dtkSettingsEditor.cpp
  dtkSpacer.cpp
  dtkSplitter.cpp
  dtkSwitch.cpp
  dtkTagCloud.cpp
  dtkTextEditor.cpp
  dtkViewManager.cpp
  dtkViewLayout.cpp
  dtkViewLayoutItem.cpp
  dtkViewList.cpp
  dtkViewListControl.cpp)

if(DTK_BUILD_SCRIPT)
set(${PROJECT_NAME}_HEADERS     ${${PROJECT_NAME}_HEADERS}     dtkInterpreter.h)
set(${PROJECT_NAME}_HEADERS_MOC ${${PROJECT_NAME}_HEADERS_MOC} dtkInterpreter.h)
set(${PROJECT_NAME}_SOURCES     ${${PROJECT_NAME}_SOURCES}     dtkInterpreter.cpp)
endif(DTK_BUILD_SCRIPT)

if(APPLE)
set(${PROJECT_NAME}_SOURCES
  ${${PROJECT_NAME}_SOURCES}
    dtkSearchField.mm)
else(APPLE)
set(${PROJECT_NAME}_SOURCES
  ${${PROJECT_NAME}_SOURCES}
    dtkSearchField.cpp)
endif(APPLE)

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
  dtkCore)

if(DTK_BUILD_SCRIPT)
target_link_libraries(${PROJECT_NAME} dtkScript)
endif(DTK_BUILD_SCRIPT)

if(APPLE)
target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
endif(APPLE)

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
