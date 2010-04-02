### dtkBuild.cmake --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Fri Apr  2 09:05:55 2010 (+0200)
## Version: $Id$
## Last-Updated: Fri Apr  2 14:13:38 2010 (+0200)
##           By: Julien Wintz
##     Update #: 28
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

set(CMAKE_BUILD_TYPE Release CACHE STRING "dtk build type")

set(CMAKE_COLOR_MAKEFILE ON)
set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)

mark_as_advanced(CMAKE_BACKWARDS_COMPATIBILITY)
mark_as_advanced(CMAKE_BUILD_TYPE)
mark_as_advanced(CMAKE_INSTALL_PREFIX)
if(APPLE)
  mark_as_advanced(CMAKE_OSX_ARCHITECTURES)
  mark_as_advanced(CMAKE_OSX_DEPLOYMENT_TARGET)
  mark_as_advanced(CMAKE_OSX_SYSROOT)
endif(APPLE)

## #################################################################
## Settings specific to the build tree.
## #################################################################

include(CMakeExportBuildSettings)

cmake_export_build_settings(
  ${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}BuildSettings.cmake)

export_library_dependencies(
  ${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}LibraryDepends.cmake)

install(FILES
  ${${PROJECT_NAME}_SOURCE_DIR}/cmake/${PROJECT_NAME}Build.cmake
  ${${PROJECT_NAME}_SOURCE_DIR}/cmake/${PROJECT_NAME}Dart.cmake
  ${${PROJECT_NAME}_SOURCE_DIR}/cmake/${PROJECT_NAME}Dependencies.cmake
  ${${PROJECT_NAME}_SOURCE_DIR}/cmake/${PROJECT_NAME}Install.cmake
  ${${PROJECT_NAME}_SOURCE_DIR}/cmake/${PROJECT_NAME}Nightly.cmake
  ${${PROJECT_NAME}_SOURCE_DIR}/cmake/${PROJECT_NAME}Pack.cmake
  ${${PROJECT_NAME}_SOURCE_DIR}/cmake/${PROJECT_NAME}Paths.cmake
  ${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}Use.cmake
  ${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}Config.cmake
  ${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}Uninstall.cmake
  ${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}LibraryDepends.cmake
  ${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}BuildSettings.cmake
  DESTINATION
  ${CMAKE_INSTALL_PREFIX}/cmake)

## Settings specific to the build tree.

set(${PROJECT_NAME}_CONFIG_INSTALL_ONLY)

set(${PROJECT_NAME}_USE_FILE_CONFIG
  ${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}Use.cmake)

set(${PROJECT_NAME}_BUILD_SETTINGS_FILE_CONFIG 
  ${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}BuildSettings.cmake)

set(${PROJECT_NAME}_LIBRARY_DIRS_CONFIG ${${PROJECT_NAME}_LIBRARY_DIRS})

set(${PROJECT_NAME}_RUNTIME_DIRS_CONFIG ${${PROJECT_NAME}_RUNTIME_DIRS})

set(${PROJECT_NAME}_INCLUDE_DIRS_CONFIG ${${PROJECT_NAME}_INCLUDE_PATH})

set(${PROJECT_NAME}_LIBRARY_DEPENDS_FILE 
  ${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}LibraryDepends.cmake)

set(${PROJECT_NAME}_CMAKE_DIR_CONFIG ${${PROJECT_NAME}_CMAKE_DIR})

set(${PROJECT_NAME}_CONFIGURATION_TYPES_CONFIG ${${PROJECT_NAME}_CONFIGURATION_TYPES})

set(${PROJECT_NAME}_BUILD_TYPE_CONFIG ${CMAKE_BUILD_TYPE})

configure_file(
  ${CMAKE_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in
  ${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}Config.cmake
  @ONLY IMMEDIATE)

configure_file(
  ${CMAKE_SOURCE_DIR}/cmake/${PROJECT_NAME}Use.cmake.in
  ${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}Use.cmake
  @ONLY IMMEDIATE)

## #################################################################
## Settings specific to the install tree.
## #################################################################

set(DOLLAR "$")

set(${PROJECT_NAME}_USE_FILE_CONFIG 
  ${DOLLAR}{${PROJECT_NAME}_INSTALL_PREFIX}${${PROJECT_NAME}_INSTALL_PACKAGE_DIR}/${PROJECT_NAME}Use.cmake)

set(${PROJECT_NAME}_BUILD_SETTINGS_FILE_CONFIG 
  ${DOLLAR}{${PROJECT_NAME}_INSTALL_PREFIX}${${PROJECT_NAME}_INSTALL_PACKAGE_DIR}/${PROJECT_NAME}BuildSettings.cmake)

if(CYGWIN AND ${PROJECT_NAME}_BUILD_SHARED_LIBS)
  set(${PROJECT_NAME}_LIBRARY_DIRS_CONFIG 
    ${DOLLAR}{${PROJECT_NAME}_INSTALL_PREFIX}${${PROJECT_NAME}_INSTALL_BIN_DIR})
else(CYGWIN AND ${PROJECT_NAME}_BUILD_SHARED_LIBS)
  set(${PROJECT_NAME}_LIBRARY_DIRS_CONFIG 
    ${DOLLAR}{${PROJECT_NAME}_INSTALL_PREFIX}${${PROJECT_NAME}_INSTALL_LIB_DIR})
endif(CYGWIN AND ${PROJECT_NAME}_BUILD_SHARED_LIBS)

if(WIN32)
  set(${PROJECT_NAME}_RUNTIME_DIRS_CONFIG 
    ${DOLLAR}{${PROJECT_NAME}_INSTALL_PREFIX}${${PROJECT_NAME}_INSTALL_BIN_DIR})
else(WIN32)
  set(${PROJECT_NAME}_RUNTIME_DIRS_CONFIG 
    ${DOLLAR}{${PROJECT_NAME}_INSTALL_PREFIX}${${PROJECT_NAME}_INSTALL_LIB_DIR})
endif(WIN32)

set(${PROJECT_NAME}_INCLUDE_DIRS_CONFIG
  ${DOLLAR}{${PROJECT_NAME}_INSTALL_PREFIX}${${PROJECT_NAME}_INSTALL_INCLUDE_DIR})

set(${PROJECT_NAME}_LIBRARY_DEPENDS_FILE 
  ${DOLLAR}{${PROJECT_NAME}_INSTALL_PREFIX}${${PROJECT_NAME}_INSTALL_PACKAGE_DIR}/${PROJECT_NAME}LibraryDepends.cmake)

set(${PROJECT_NAME}_CMAKE_DIR_CONFIG 
  ${DOLLAR}{${PROJECT_NAME}_INSTALL_PREFIX}${${PROJECT_NAME}_INSTALL_PACKAGE_DIR}/CMake)

set(${PROJECT_NAME}_CONFIGURATION_TYPES_CONFIG)

string(REGEX REPLACE "/" ";" ${PROJECT_NAME}_INSTALL_PACKAGE_DIR_COUNT
  "${${PROJECT_NAME}_INSTALL_PACKAGE_DIR}")
set(${PROJECT_NAME}_CONFIG_INSTALL_ONLY "
# Compute the installation prefix from ${PROJECT_NAME}_DIR.
set(${PROJECT_NAME}_INSTALL_PREFIX \"${DOLLAR}{${PROJECT_NAME}_DIR}\")
")
foreach(p ${${PROJECT_NAME}_INSTALL_PACKAGE_DIR_COUNT})
  set(${PROJECT_NAME}_CONFIG_INSTALL_ONLY
    "${${PROJECT_NAME}_CONFIG_INSTALL_ONLY}GET_FILENAME_COMPONENT(${PROJECT_NAME}_INSTALL_PREFIX \"${DOLLAR}{${PROJECT_NAME}_INSTALL_PREFIX}\" PATH)\n"
    )
endforeach(p)

if(CMAKE_CONFIGURATION_TYPES)
  foreach(config ${CMAKE_CONFIGURATION_TYPES})
    set(${PROJECT_NAME}_BUILD_TYPE_CONFIG ${config})
    configure_file(
      ${CMAKE_CURRENT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in
      ${${PROJECT_NAME}_BINARY_DIR}/Install/${config}/${PROJECT_NAME}Config.cmake
      @ONLY IMMEDIATE)
    configure_file(
      ${CMAKE_CURRENT_SOURCE_DIR}/cmake/${PROJECT_NAME}Use.cmake.in
      ${${PROJECT_NAME}_BINARY_DIR}/Install/${config}/${PROJECT_NAME}Use.cmake
      @ONLY IMMEDIATE)
  endforeach(config)

  if(NOT ${PROJECT_NAME}_INSTALL_NO_DEVELOPMENT)
    install(FILES ${${PROJECT_NAME}_BINARY_DIR}/Install/${DOLLAR}{BUILD_TYPE}/${PROJECT_NAME}Config.cmake DESTINATION ${${PROJECT_NAME}_INSTALL_PACKAGE_DIR})
  endif(NOT ${PROJECT_NAME}_INSTALL_NO_DEVELOPMENT)
else(CMAKE_CONFIGURATION_TYPES)
  set(${PROJECT_NAME}_BUILD_TYPE_CONFIG ${CMAKE_BUILD_TYPE})
  configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in
    ${${PROJECT_NAME}_BINARY_DIR}/Install/${PROJECT_NAME}Config.cmake
    @ONLY IMMEDIATE)
  configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/${PROJECT_NAME}Use.cmake.in
    ${${PROJECT_NAME}_BINARY_DIR}/Install/${PROJECT_NAME}Use.cmake
    @ONLY IMMEDIATE)

  if(NOT ${PROJECT_NAME}_INSTALL_NO_DEVELOPMENT)
    install(FILES ${${PROJECT_NAME}_BINARY_DIR}/Install/${PROJECT_NAME}Config.cmake
      DESTINATION ${CMAKE_INSTALL_PREFIX}/cmake/)
    install(FILES ${${PROJECT_NAME}_BINARY_DIR}/Install/${PROJECT_NAME}Use.cmake
      DESTINATION ${CMAKE_INSTALL_PREFIX}/cmake/)
  endif(NOT ${PROJECT_NAME}_INSTALL_NO_DEVELOPMENT)
endif(CMAKE_CONFIGURATION_TYPES)

## #################################################################
## Uninstall target
## #################################################################

configure_file("${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}Uninstall.cmake.in"
               "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Uninstall.cmake"
               IMMEDIATE @ONLY)

add_custom_target(uninstall
  "${CMAKE_COMMAND}" -P
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Uninstall.cmake")
