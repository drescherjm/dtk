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

cmake_minimum_required(VERSION 2.8.11)

######################################################################

project(dtk)

## ###################################################################
## Version setup
## ###################################################################

set(dtk_VERSION_MAJOR 1)
set(dtk_VERSION_MINOR 0)
set(dtk_VERSION_PATCH 0)
set(dtk_VERSION
  ${dtk_VERSION_MAJOR}.${dtk_VERSION_PATCH}.${dtk_VERSION_PATCH})

## ###################################################################
## Path setup
## ###################################################################

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

## #################################################################
## Install prefix
## #################################################################

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/install" CACHE PATH "${PROJECT_NAME} install prefix" FORCE)
endif(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

## ###################################################################
## Build setup
## ###################################################################

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include(GNUInstallDirs)
include(GenerateExportHeader)

if(APPLE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -I/usr/lib/c++/v1")
endif(APPLE)

if(NOT APPLE AND NOT MSVC)
  include(CheckCXXCompilerFlag)
  CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
  CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
  if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wno-unknown-pragmas")
  elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wno-unknown-pragmas")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unknown-pragmas")
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
  endif()
else(NOT APPLE AND NOT MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif(NOT APPLE AND NOT MSVC)

if(CMAKE_SIZEOF_VOID_P MATCHES 8)
  set(DTK_BUILD_32 0)
  set(DTK_BUILD_64 1)
else(CMAKE_SIZEOF_VOID_P MATCHES 8)
  set(DTK_BUILD_32 1)
  set(DTK_BUILD_64 0)
endif(CMAKE_SIZEOF_VOID_P MATCHES 8)

## ###################################################################
## Test setup
## ###################################################################

enable_testing()

## #################################################################
## Options
## #################################################################

option(DTK_BUILD_SUPPORT_CORE        "Build support layer" false)
option(DTK_BUILD_SUPPORT_CONTAINER   "Build support layer" false)
option(DTK_BUILD_SUPPORT_COMPOSER    "Build support layer" false)
option(DTK_BUILD_SUPPORT_DISTRIBUTED "Build support layer" false)
option(DTK_BUILD_SUPPORT_GUI         "Build support layer" false)
option(DTK_BUILD_SUPPORT_MATH        "Build support layer" false)
option(DTK_BUILD_SUPPORT_PLOT        "Build support layer" false)

## #################################################################
## Dependencies
## #################################################################

find_package(Qt5Core        REQUIRED)
find_package(Qt5Quick       REQUIRED)
find_package(Qt5Network     REQUIRED)
find_package(Qt5Gui         REQUIRED)
find_package(Qt5Xml         REQUIRED)
find_package(Qt5Declarative REQUIRED)

## #################################################################
## Dependencies - Optional                           [TO BE REMOVED]
## #################################################################

set(DTK_HAVE_MPI "NO")

if(DTK_BUILD_SUPPORT_DISTRIBUTED)

find_package(MPI QUIET)

if(MPI_FOUND)
  include_directories(${MPI_INCLUDE_PATH})
  set(COMPILE_FLAGS ${COMPILE_FLAGS} ${MPI_COMPILE_FLAGS})
  set(DTK_HAVE_MPI "YES")
endif(MPI_FOUND)

endif(DTK_BUILD_SUPPORT_DISTRIBUTED)

## #################################################################
## Dependencies - internal
## #################################################################

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/dtk)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/dtkComposer)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/dtkCore)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/dtkDistributed)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/dtkLog)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/dtkMath)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/dtkTest)

## ###################################################################
## Input
## ###################################################################

add_subdirectory(src)
add_subdirectory(tst)
add_subdirectory(app)
add_subdirectory(doc)

## ###################################################################
## Exporting
## ###################################################################

export(PACKAGE dtk)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/dtkConfig.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/dtkConfig.cmake" @ONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/dtkConfig.install.cmake.in
  "${PROJECT_BINARY_DIR}/install/dtkConfig.cmake" @ONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/dtkConfigVersion.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/dtkConfigVersion.cmake" @ONLY)

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/install/dtkConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/dtkConfigVersion.cmake"
  DESTINATION lib/cmake/dtk)

install(EXPORT dtkDepends DESTINATION lib/cmake/dtk)

## ###################################################################
## Beautifying
## ###################################################################

mark_as_advanced(dtk_VERSION_MAJOR)
mark_as_advanced(dtk_VERSION_MINOR)
mark_as_advanced(dtk_VERSION_BUILD)

mark_as_advanced(Qt5Concurrent_DIR)
mark_as_advanced(Qt5Core_DIR)
mark_as_advanced(Qt5Declarative_DIR)
mark_as_advanced(Qt5Gui_DIR)
mark_as_advanced(Qt5Network_DIR)
mark_as_advanced(Qt5Qml_DIR)
mark_as_advanced(Qt5Quick_DIR)
mark_as_advanced(Qt5QuickTest_DIR)
mark_as_advanced(Qt5Script_DIR)
mark_as_advanced(Qt5Test_DIR)
mark_as_advanced(Qt5Widgets_DIR)
mark_as_advanced(Qt5Xml_DIR)

mark_as_advanced(CMAKE_AR)
mark_as_advanced(CMAKE_BUILD_TYPE)
mark_as_advanced(CMAKE_INSTALL_PREFIX)
mark_as_advanced(CMAKE_OSX_ARCHITECTURES)
mark_as_advanced(CMAKE_OSX_DEPLOYMENT_TARGET)
mark_as_advanced(CMAKE_OSX_SYSROOT)

mark_as_advanced(MPI_EXTRA_LIBRARY)
mark_as_advanced(MPI_LIBRARY)

## ###################################################################
## Packaging
## ###################################################################

include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_VERSION_MAJOR "${dtk_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${dtk_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${dtk_VERSION_PATCH}")

include(CPack)

######################################################################
### CMakeLists.txt ends here
