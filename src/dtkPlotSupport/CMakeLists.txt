### CMakeLists.txt ---
##
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Mon Nov 22 10:20:27 2010 (+0100)
######################################################################
##
### Commentary:
##
######################################################################
##
### Change log:
##
######################################################################

project(dtkPlotSupport)

find_package(Qwt 6 REQUIRED)

if(QWT_FOUND)

include_directories(${QWT_INCLUDE_DIR})

## #################################################################
## Sources
## #################################################################

set(${PROJECT_NAME}_HEADERS
  dtkPlotCurve.h
  dtkPlotRenderer.h
  dtkPlotView.h
  dtkPlotViewPanner.h
  dtkPlotViewPicker.h
  dtkPlotViewZoomer.h
  dtkPlotViewLegend.h
  dtkPlotViewLegend_p.h
  dtkPlotViewGrid.h
  dtkPlotViewSettings.h
  dtkPlotViewToolBar.h)

set(${PROJECT_NAME}_SOURCES
  dtkPlotCurve.cpp
  dtkPlotRenderer.cpp
  dtkPlotView.cpp
  dtkPlotViewPanner.cpp
  dtkPlotViewPicker.cpp
  dtkPlotViewZoomer.cpp
  dtkPlotViewLegend.cpp
  dtkPlotViewGrid.cpp
  dtkPlotViewSettings.cpp
  dtkPlotViewToolBar.cpp)

set(${PROJECT_NAME}_SOURCES_QRC dtkPlot.qrc)

## #################################################################
## Build rules
## #################################################################

qt5_add_resources(${PROJECT_NAME}_SOURCES_QRC ${${PROJECT_NAME}_SOURCES_QRC})

add_library(${PROJECT_NAME} SHARED
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_HEADERS}
  ${${PROJECT_NAME}_SOURCES_QRC})

target_link_libraries(${PROJECT_NAME}
  ${QWT_LIBRARIES}
  dtkCoreSupport
  dtkGuiSupport)

## ###################################################################
## Link rules
## ###################################################################

target_link_libraries(${PROJECT_NAME} Qt5::Core)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)

## #################################################################
## Target properties
## #################################################################

set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_RPATH 0)
set_target_properties(${PROJECT_NAME} PROPERTIES INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
set_target_properties(${PROJECT_NAME} PROPERTIES INSTALL_RPATH    "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")

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
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
      COMPONENT plotsupport
         EXPORT dtkDepends)

endif(QWT_FOUND)
