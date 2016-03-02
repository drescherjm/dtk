## Version: $Id$
##
######################################################################
##
### Commentary:
##
######################################################################
##
### Change Log:
##
######################################################################
##
### Code:

project(dtkMonitoring)

## #################################################################
## Input
## #################################################################

set(${PROJECT_NAME}_HEADERS
  dtkMonitor
  dtkMonitor.h
  dtkMonitorBoolean
  dtkMonitorBoolean.h
  dtkMonitorBooleanSimple
  dtkMonitorBooleanSimple.h
  dtkMonitoring
  dtkMonitoringController
  dtkMonitoringController.h
  dtkMonitoringFactory
  dtkMonitoringFactory.h
  dtkMonitoringList
  dtkMonitoringList.h
  dtkMonitoringModel
  dtkMonitoringModel.h
  dtkMonitoringReader
  dtkMonitoringReader.h
  dtkMonitoringScene
  dtkMonitoringScene.h
  dtkMonitoringView
  dtkMonitoringView.h
  dtkMonitoringWriter
  dtkMonitoringWriter.h
  dtkMonitorInteger
  dtkMonitorInteger.h
  dtkMonitorIntegerSimple
  dtkMonitorIntegerSimple.h
  dtkMonitorReal
  dtkMonitorReal.h
  dtkMonitorRealSimple
  dtkMonitorRealSimple.h
)

set(${PROJECT_NAME}_SOURCES
  dtkMonitor.cpp
  dtkMonitorBoolean.cpp
  dtkMonitorBooleanSimple.cpp
  dtkMonitoringController.cpp
  dtkMonitoringFactory.cpp
  dtkMonitoringList.cpp
  dtkMonitoringModel.cpp
  dtkMonitoringReader.cpp
  dtkMonitoringScene.cpp
  dtkMonitoringView.cpp
  dtkMonitoringWriter.cpp
  dtkMonitorInteger.cpp
  dtkMonitorIntegerSimple.cpp
  dtkMonitorReal.cpp
  dtkMonitorRealSimple.cpp
)

set(${PROJECT_NAME}_RCC dtkMonitoring.qrc)

## #################################################################
## Build rules
## #################################################################

qt5_add_resources(${PROJECT_NAME}_SOURCES_QRC ${${PROJECT_NAME}_RCC})

add_library(${PROJECT_NAME} SHARED
  ${${PROJECT_NAME}_SOURCES_QRC}
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_HEADERS})

## ###################################################################
## Link rules
## ###################################################################


target_link_libraries(${PROJECT_NAME} dtkMeta dtkLog dtkComposer)

target_link_libraries(${PROJECT_NAME} Qt5::Core)
target_link_libraries(${PROJECT_NAME} Qt5::Gui)
target_link_libraries(${PROJECT_NAME} Qt5::Xml)
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
 "${CMAKE_BINARY_DIR}/${PROJECT_NAME}Export"
 "${CMAKE_BINARY_DIR}/${PROJECT_NAME}Export.h")

## ###################################################################
## Install rules - files
## ###################################################################

install(FILES ${${PROJECT_NAME}_HEADERS}
  DESTINATION include/${PROJECT_NAME}
    COMPONENT core)

## ###################################################################
## Install rules - targets
## ###################################################################

install(TARGETS ${PROJECT_NAME}
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
      COMPONENT core
         EXPORT dtkDepends)

######################################################################
### CMakeLists.txt ends here
