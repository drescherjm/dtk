### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Mon Jul 20 18:30:43 2009 (+0200)
## Version: $Id$
## Last-Updated: Fri Sep  4 21:51:34 2009 (+0200)
##           By: Julien Wintz
##     Update #: 193
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

cmake_minimum_required(VERSION 2.6)

project(dtk)

## #################################################################
## Setup version numbering
## #################################################################

set(${PROJECT_NAME}_VERSION_MAJOR 0 CACHE STRING "dtk major version number.")
set(${PROJECT_NAME}_VERSION_MINOR 1 CACHE STRING "dtk minor version number.")
set(${PROJECT_NAME}_VERSION_BUILD 0 CACHE STRING "dtk build version number.")
set(${PROJECT_NAME}_VERSION
  "${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}.${${PROJECT_NAME}_VERSION_BUILD}")

mark_as_advanced(${PROJECT_NAME}_VERSION_MAJOR)
mark_as_advanced(${PROJECT_NAME}_VERSION_MINOR)
mark_as_advanced(${PROJECT_NAME}_VERSION_BUILD)

set(CMAKE_COLOR_MAKEFILE ON)
set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)

## #################################################################
## Setup output paths
## #################################################################

if(WIN32)
  set(${PROJECT_NAME}_ARCHIVE_OUTPUT_DIRECTORY lib)
  set(${PROJECT_NAME}_RUNTIME_OUTPUT_DIRECTORY bin)
  set(${PROJECT_NAME}_LIBRARY_OUTPUT_DIRECTORY bin)
else(WIN32)
  set(${PROJECT_NAME}_ARCHIVE_OUTPUT_DIRECTORY lib)
  set(${PROJECT_NAME}_RUNTIME_OUTPUT_DIRECTORY bin)
  set(${PROJECT_NAME}_LIBRARY_OUTPUT_DIRECTORY lib)
endif(WIN32)

set(CMAKE_DEBUG_POSTFIX "d")

set(LIBRARY_OUTPUT_PATH    ${CMAKE_BINARY_DIR}/${${PROJECT_NAME}_LIBRARY_OUTPUT_DIRECTORY})
set(ARCHIVE_OUTPUT_PATH    ${CMAKE_BINARY_DIR}/${${PROJECT_NAME}_ARCHIVE_OUTPUT_DIRECTORY})
set(RUNTIME_OUTPUT_PATH    ${CMAKE_BINARY_DIR}/${${PROJECT_NAME}_RUNTIME_OUTPUT_DIRECTORY})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/${${PROJECT_NAME}_RUNTIME_OUTPUT_DIRECTORY})

set(${PROJECT_NAME}_INCLUDE_PATH ${CMAKE_SOURCE_DIR}/src)

set(${PROJECT_NAME}_LIBRARY_DIRS ${LIBRARY_OUTPUT_PATH})
set(${PROJECT_NAME}_RUNTIME_DIRS ${RUNTIME_OUTPUT_PATH})

## #################################################################
## Setup CMake Modules
## #################################################################

set(${PROJECT_NAME}_CMAKE_DIR
  "${CMAKE_SOURCE_DIR}/cmake" CACHE INTERNAL "")

set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH} "${${PROJECT_NAME}_CMAKE_DIR}")

if(NOT ${PROJECT_NAME}_INSTALL_NO_DEVELOPMENT)
  install_files(${${PROJECT_NAME}_INSTALL_PACKAGE_DIR}/cmake "\\.cmake$")
endif(NOT ${PROJECT_NAME}_INSTALL_NO_DEVELOPMENT)

## #################################################################
## Setup installation settings
## #################################################################

set(${PROJECT_NAME}_CONFIGURATION_TYPES ${CMAKE_CONFIGURATION_TYPES})

if(NOT ${PROJECT_NAME}_INSTALL_BIN_DIR)
  set(${PROJECT_NAME}_INSTALL_BIN_DIR "/bin")
endif(NOT ${PROJECT_NAME}_INSTALL_BIN_DIR)

if(NOT ${PROJECT_NAME}_INSTALL_LIB_DIR)
  set(${PROJECT_NAME}_INSTALL_LIB_DIR "/lib")
endif(NOT ${PROJECT_NAME}_INSTALL_LIB_DIR)

if(NOT ${PROJECT_NAME}_INSTALL_DATA_DIR)
  set(${PROJECT_NAME}_INSTALL_DATA_DIR "/share" CACHE INTERNAL "")
endif(NOT ${PROJECT_NAME}_INSTALL_DATA_DIR)

if(NOT ${PROJECT_NAME}_INSTALL_INCLUDE_DIR)
  set(${PROJECT_NAME}_INSTALL_INCLUDE_DIR "/include")
endif(NOT ${PROJECT_NAME}_INSTALL_INCLUDE_DIR)

if(NOT ${PROJECT_NAME}_INSTALL_PACKAGE_DIR)
  set(${PROJECT_NAME}_INSTALL_PACKAGE_DIR ${${PROJECT_NAME}_INSTALL_LIB_DIR} CACHE INTERNAL "")
endif(NOT ${PROJECT_NAME}_INSTALL_PACKAGE_DIR)

if(NOT ${PROJECT_NAME}_INSTALL_NO_DEVELOPMENT)
  set(${PROJECT_NAME}_INSTALL_NO_DEVELOPMENT 0)
endif(NOT ${PROJECT_NAME}_INSTALL_NO_DEVELOPMENT)

if(NOT ${PROJECT_NAME}_INSTALL_NO_RUNTIME)
  set(${PROJECT_NAME}_INSTALL_NO_RUNTIME 0)
endif(NOT ${PROJECT_NAME}_INSTALL_NO_RUNTIME)

if(NOT ${PROJECT_NAME}_INSTALL_NO_DOCUMENTATION)
  set(${PROJECT_NAME}_INSTALL_NO_DOCUMENTATION 0)
endif(NOT ${PROJECT_NAME}_INSTALL_NO_DOCUMENTATION)

set(${PROJECT_NAME}_INSTALL_NO_LIBRARIES)
if(${PROJECT_NAME}_BUILD_SHARED_LIBS)
  if(${PROJECT_NAME}_INSTALL_NO_RUNTIME AND ${PROJECT_NAME}_INSTALL_NO_DEVELOPMENT)
    set(${PROJECT_NAME}_INSTALL_NO_LIBRARIES 1)
  endif(${PROJECT_NAME}_INSTALL_NO_RUNTIME AND ${PROJECT_NAME}_INSTALL_NO_DEVELOPMENT)
else(${PROJECT_NAME}_BUILD_SHARED_LIBS)
  if(${PROJECT_NAME}_INSTALL_NO_DEVELOPMENT)
    set(${PROJECT_NAME}_INSTALL_NO_LIBRARIES 1)
  endif(${PROJECT_NAME}_INSTALL_NO_DEVELOPMENT)
endif(${PROJECT_NAME}_BUILD_SHARED_LIBS)

## #################################################################
## Setup testing
## #################################################################

# include(CTest)

## #################################################################
## Resolve dependencies
## #################################################################

mark_as_advanced(CMAKE_BACKWARDS_COMPATIBILITY)
mark_as_advanced(CMAKE_BUILD_TYPE)
mark_as_advanced(CMAKE_INSTALL_PREFIX)
if(APPLE)
  mark_as_advanced(CMAKE_OSX_ARCHITECTURES)
  mark_as_advanced(CMAKE_OSX_SYSROOT)
endif(APPLE)

set(QT_USE_QTOPENGL  TRUE)
set(QT_USE_QTSQL     TRUE)
set(QT_USE_QTHELP    TRUE)
set(QT_USE_QTNETWORK TRUE)
set(QT_USE_QTWEBKIT  TRUE)

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})

mark_as_advanced(QT_QMAKE_EXECUTABLE)

find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})
set(CMAKE_SWIG_FLAGS "")

macro(dtk_wrap project target name language input deps)

  set(wrap_output ${project}_wrap_${language}.cpp)

  add_custom_command(
    OUTPUT ${wrap_output}
    COMMAND ${SWIG_EXECUTABLE}
    ARGS
      "-${language}"
      "-c++"
      "-module" ${name}
      "-I${dtk_INCLUDE_PATH}"
      "-outdir" ${CMAKE_CURRENT_BINARY_DIR}
      "-o" ${wrap_output}
      ${input}
    MAIN_DEPENDENCY ${input}
#   DEPENDS ${project}_wrap_${language}_DEPENDS
    COMMENT "Wrapping ${input} to ${language}")

  set(${target} ${${target}} ${wrap_output})

# add_custom_target(${project}_wrap_${language}_DEPENDS 
#   ${CMAKE_COMMAND} -E touch ${CMAKE_CURRENT_BINARY_DIR}/${project}_wrap_${language}.timestamp
#   DEPENDS ${deps})

endmacro(dtk_wrap)

mark_as_advanced(SWIG_DIR)
mark_as_advanced(SWIG_EXECUTABLE)
mark_as_advanced(SWIG_VERSION)

find_package(TCL)
if(TCL_FOUND)
  include_directories(${TCL_INCLUDE_PATH})
endif(TCL_FOUND)

find_package(PythonLibs)
if(PYTHONLIBS_FOUND)
  include_directories(${PYTHON_INCLUDE_PATH})
  get_filename_component(PYTHON_PATH ${PYTHON_LIBRARIES} PATH)
  link_directories(${PYTHON_PATH})
endif(PYTHONLIBS_FOUND)

## #################################################################
## Build options
## #################################################################

option(BUILD_SHARED_LIBS  "Build shared libraries" true)
option(BUILD_TOOLS        "Build tools"            true)
option(BUILD_EXAMPLES     "Build examples"         false)

## #################################################################
## Build rules
## #################################################################

include_directories(${${PROJECT_NAME}_INCLUDE_PATH})

add_subdirectory(src)

if(BUILD_TOOLS)
  add_subdirectory(tools)
endif(BUILD_TOOLS)

if(BUILD_EXAMPLES)
  add_subdirectory(examples)
endif(BUILD_EXAMPLES)

## #################################################################
## Configuration rules for the build tree
## #################################################################

include(CMakeExportBuildSettings)

cmake_export_build_settings(
  ${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}BuildSettings.cmake)

export_library_dependencies(
  ${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}LibraryDepends.cmake)

if(NOT ${PROJECT_NAME}_INSTALL_NO_DEVELOPMENT)
  install_files(${${PROJECT_NAME}_INSTALL_PACKAGE_DIR} FILES
    ${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}Use.cmake
    ${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}LibraryDepends.cmake
    ${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}BuildSettings.cmake
    )
endif(NOT ${PROJECT_NAME}_INSTALL_NO_DEVELOPMENT)

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

## Settings specific to the install tree.

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
    install_files(${${PROJECT_NAME}_INSTALL_PACKAGE_DIR} FILES
      ${${PROJECT_NAME}_BINARY_DIR}/Install/${DOLLAR}{BUILD_TYPE}/${PROJECT_NAME}Config.cmake)
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
    install_files(${${PROJECT_NAME}_INSTALL_PACKAGE_DIR} FILES
      ${${PROJECT_NAME}_BINARY_DIR}/Install/${PROJECT_NAME}Config.cmake)
    install_files(${${PROJECT_NAME}_INSTALL_PACKAGE_DIR} FILES
      ${${PROJECT_NAME}_BINARY_DIR}/Install/${PROJECT_NAME}Use.cmake)
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
