### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Created: Mon Feb  4 10:17:21 2013 (+0100)
## Version: 
## Last-Updated: Mon Feb 11 23:25:49 2013 (+0100)
##           By: Julien Wintz
##     Update #: 113
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

if(NOT APPLE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unknown-pragmas")
else(NOT APPLE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")
endif(NOT APPLE)

## ###################################################################
## Test setup
## ###################################################################

enable_testing()

## #################################################################
## Dependencies - Qt
## #################################################################

find_package(Qt5Concurrent REQUIRED)
find_package(Qt5Core       REQUIRED)
find_package(Qt5Gui        REQUIRED)
find_package(Qt5Network    REQUIRED)
find_package(Qt5Qml        REQUIRED)
find_package(Qt5Quick      REQUIRED)
find_package(Qt5Test       REQUIRED)
find_package(Qt5Widgets    REQUIRED)

## #################################################################
## Dependencies - internal
## #################################################################

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/src/dtk)
include_directories(${PROJECT_SOURCE_DIR}/src/dtkLog)
include_directories(${PROJECT_SOURCE_DIR}/src/dtkDistributed)
include_directories(${PROJECT_SOURCE_DIR}/src/dtkTest)

## ###################################################################
## Input
## ###################################################################

add_subdirectory(src)
add_subdirectory(test)

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
mark_as_advanced(Qt5Test_DIR)
mark_as_advanced(Qt5Widgets_DIR)

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
