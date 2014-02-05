### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Created: Mon Feb  4 10:17:21 2013 (+0100)
## Version: 
## Last-Updated: mer. févr.  5 15:49:54 2014 (+0100)
##           By: Nicolas Niclausse
##     Update #: 208
######################################################################
## 
### Change Log:
## 
######################################################################

cmake_minimum_required(VERSION 2.8.10)

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

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

## ###################################################################
## Build setup
## ###################################################################

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include("GNUInstallDirs")

if(APPLE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -I/usr/lib/c++/v1")
else(APPLE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
endif(APPLE)

if(NOT APPLE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unknown-pragmas")
else(NOT APPLE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif(NOT APPLE)

## ###################################################################
## Test setup
## ###################################################################

enable_testing()

## #################################################################
## Dependencies - Qt
## #################################################################

if(MSVC)
  option(DTK_USE_PRECOMPILED_HEADERS "Use precompiled headers" true)
endif(MSVC)

include(dtkBuild)

find_package(Qt5Concurrent REQUIRED)
find_package(Qt5Core       REQUIRED)
find_package(Qt5Gui        REQUIRED)
find_package(Qt5Network    REQUIRED)
find_package(Qt5Qml        REQUIRED)
find_package(Qt5Quick      REQUIRED)
find_package(Qt5Test       REQUIRED)
find_package(Qt5Widgets    REQUIRED)


## #################################################################
## Old options
## #################################################################

mark_as_advanced(MPI_EXTRA_LIBRARY)
mark_as_advanced(MPI_LIBRARY)
mark_as_advanced(DTK_BUILD_MPI)

find_package(MPI QUIET)


option(DTK_BUILD_DISTRIBUTED_SUPPORT   "Build distributed support layer" true)
option(DTK_BUILD_COMPOSER_SUPPORT      "Build composer support layer"    true)
option(DTK_BUILD_PLOT_SUPPORT          "Build plotting support layer"    true)
option(DTK_BUILD_MPI                   "Build MPI support "              true)

if(DTK_BUILD_MPI)
  if(MPI_FOUND)
    include_directories(${MPI_INCLUDE_PATH})
    set(COMPILE_FLAGS ${COMPILE_FLAGS} ${MPI_COMPILE_FLAGS})
    set(DTK_HAVE_MPI "YES")
  endif(MPI_FOUND)
endif(DTK_BUILD_MPI)



## #################################################################
## Dependencies - internal
## #################################################################

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/src/dtk)
include_directories(${PROJECT_SOURCE_DIR}/src/dtkCore)
include_directories(${PROJECT_SOURCE_DIR}/src/dtkMath)
include_directories(${PROJECT_SOURCE_DIR}/src/dtkDistributed)
include_directories(${PROJECT_SOURCE_DIR}/src/dtkTest)
include_directories(${PROJECT_SOURCE_DIR}/src/dtkWidgets)

## ###################################################################
## Input
## ###################################################################

add_subdirectory(src)
add_subdirectory(qml)
add_subdirectory(tst)

## ###################################################################
## Exporting
## ###################################################################

export(PACKAGE dtk)

configure_file(${PROJECT_SOURCE_DIR}/cmake/dtkConfig.cmake.in
  "${PROJECT_BINARY_DIR}/dtkConfig.cmake" @ONLY)
configure_file(${PROJECT_SOURCE_DIR}/cmake/dtkConfigVersion.cmake.in
  "${PROJECT_BINARY_DIR}/dtkConfigVersion.cmake" @ONLY)

install(FILES
  "${PROJECT_BINARY_DIR}/dtkConfig.cmake"
  "${PROJECT_BINARY_DIR}/dtkConfigVersion.cmake"
  DESTINATION lib/cmake/dtk)

install(EXPORT dtkDepends
  DESTINATION lib/cmake/dtk)

## ###################################################################
## Beautifying
## ###################################################################

mark_as_advanced(dtk_VERSION_MAJOR)
mark_as_advanced(dtk_VERSION_MINOR)
mark_as_advanced(dtk_VERSION_BUILD)

mark_as_advanced(Qt5Concurrent_DIR)
mark_as_advanced(Qt5Core_DIR)
mark_as_advanced(Qt5Gui_DIR)
mark_as_advanced(Qt5Network_DIR)
mark_as_advanced(Qt5Qml_DIR)
mark_as_advanced(Qt5Quick_DIR)
mark_as_advanced(Qt5QuickTest_DIR)
mark_as_advanced(Qt5Test_DIR)
mark_as_advanced(Qt5Widgets_DIR)
mark_as_advanced(Qt5Xml_DIR)

mark_as_advanced(CMAKE_AR)
mark_as_advanced(CMAKE_BUILD_TYPE)
mark_as_advanced(CMAKE_INSTALL_PREFIX)
mark_as_advanced(CMAKE_OSX_ARCHITECTURES)
mark_as_advanced(CMAKE_OSX_DEPLOYMENT_TARGET)
mark_as_advanced(CMAKE_OSX_SYSROOT)

## ###################################################################
## Packaging
## ###################################################################

include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_VERSION_MAJOR "${dtk_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${dtk_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${dtk_VERSION_PATCH}")

include(CPack)
