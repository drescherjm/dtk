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

project(dtkCore)

## #################################################################
## Input
## #################################################################

set(${PROJECT_NAME}_HEADERS
  dtkAbstractApplication.h
  dtkArray
  dtkArray.h
  dtkArray.tpp
  dtkArrayData
  dtkArrayData.h
  dtkCore
  dtkCore.h
  dtkCoreApplication.h
  dtkCorePlugin
  dtkCorePlugin.h
  dtkCorePluginFactory
  dtkCorePluginFactory.h
  dtkCorePluginFactory.tpp
  dtkCorePluginFactoryTemplate
  dtkCorePluginFactoryTemplate.h
  dtkCorePluginManager
  dtkCorePluginManager.h
  dtkCorePluginManager.tpp
  dtkCoreSettings
  dtkCoreSettings.h
  dtkIterator
  dtkIterator.h
  dtkSpinLock.h)

set(${PROJECT_NAME}_SOURCES
  dtkAbstractApplication.cpp
  dtkCoreApplication.cpp
  dtkCoreSettings.cpp
  dtkArrayData.cpp)

## #################################################################
## Build rules
## #################################################################

add_library(${PROJECT_NAME} SHARED
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_HEADERS})

## ###################################################################
## Link rules
## ###################################################################

qt5_use_modules(${PROJECT_NAME} Core)

target_link_libraries(${PROJECT_NAME} dtkMeta dtkLog)

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
