### CMakeLists.txt ---
##
## Author: Julien Wintz
## Created: Mon Apr 15 11:46:27 2013 (+0200)
## Version:
## Last-Updated: lun. avril  7 11:13:47 2014 (+0200)
##           By: Nicolas Niclausse
##     Update #: 58
######################################################################
##
### Change Log:
##
######################################################################

project(dtkWidgets)

## #################################################################
## Input
## #################################################################

set(${PROJECT_NAME}_HEADERS
  dtkNotifiable.h
  dtkNotification.h
  dtkNotificationDisplay.h
  dtkNotificationEvent.h
  dtkNotificationQueue.h
  dtkObjectEditor.h
  dtkPropertyEditor.h
  dtkPropertyEditorFactory.h
  dtkToolBox.h
  dtkWidgetsLogView.h
  dtkWidgetsLogView_p.h
  dtkWidgetsTag.h
  dtkWidgetsTagCloud.h
  dtkWidgetsTagCloudController.h
  dtkWidgetsTagCloudDesc.h
  dtkWidgetsTagCloudItem.h
  dtkWidgetsTagCloudLayout.h
  dtkWidgetsTagCloudList.h
  dtkWidgetsTagCloudScope.h
  dtkWidgetsTagCloudScopeItem.h
  dtkWidgetsTagCloudView.h)

set(${PROJECT_NAME}_SOURCES
  dtkNotification.cpp
  dtkNotificationDisplay.cpp
  dtkNotificationEvent.cpp
  dtkNotificationQueue.cpp
  dtkObjectEditor.cpp
  dtkPropertyEditor.cpp
  dtkPropertyEditorFactory.cpp
  dtkToolBox.cpp
  dtkWidgetsLogView.cpp
  dtkWidgetsTag.cpp
  dtkWidgetsTagCloud.cpp
  dtkWidgetsTagCloudController.cpp
  dtkWidgetsTagCloudDesc.cpp
  dtkWidgetsTagCloudItem.cpp
  dtkWidgetsTagCloudLayout.cpp
  dtkWidgetsTagCloudList.cpp
  dtkWidgetsTagCloudScope.cpp
  dtkWidgetsTagCloudScopeItem.cpp
  dtkWidgetsTagCloudView.cpp)

set(${PROJECT_NAME}_SOURCES_RCC
  dtkNotification.qrc
  dtkWidgetsTagCloud.qrc)

## #################################################################
## Build rules
## #################################################################

qt5_add_resources(${PROJECT_NAME}_SOURCES_QRC ${${PROJECT_NAME}_SOURCES_RCC})

add_library(${PROJECT_NAME} SHARED
  ${${PROJECT_NAME}_SOURCES_QRC}
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_HEADERS})

target_link_libraries(${PROJECT_NAME}
  dtkLog)

## ###################################################################
## Link rules
## ###################################################################

target_link_libraries(${PROJECT_NAME} Qt5::Core)
target_link_libraries(${PROJECT_NAME} Qt5::Gui)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)

## ###################################################################
## Target properties
## ###################################################################

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
    COMPONENT widgets)

## ###################################################################
## Install rules - targets
## ###################################################################

install(TARGETS ${PROJECT_NAME}
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
      COMPONENT widgets
         EXPORT dtkDepends)
