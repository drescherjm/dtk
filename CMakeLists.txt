### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Created: Mon Feb  4 10:17:21 2013 (+0100)
## Version: 
## Last-Updated: Mon Feb  4 16:53:26 2013 (+0100)
##           By: Julien Wintz
##     Update #: 59
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

set(${PROJECT_NAME}_VERSION_MAJOR 1)
set(${PROJECT_NAME}_VERSION_MINOR 0)
set(${PROJECT_NAME}_VERSION_PATCH 0)

## ###################################################################
## Build setup
## ###################################################################

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(NOT APPLE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unknown-pragmas")
else(NOT APPLE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")
endif(NOT APPLE)

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

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/src/dtk)
include_directories(${CMAKE_SOURCE_DIR}/src/dtkDistributed)
include_directories(${CMAKE_SOURCE_DIR}/src/dtkTest)

## ###################################################################
## Input
## ###################################################################

add_subdirectory(src)
add_subdirectory(test)

## ###################################################################
## Beautifying
## ###################################################################

mark_as_advanced(${PROJECT_NAME}_VERSION_MAJOR)
mark_as_advanced(${PROJECT_NAME}_VERSION_MINOR)
mark_as_advanced(${PROJECT_NAME}_VERSION_BUILD)

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

set(CPACK_PACKAGE_VERSION_MAJOR "${${PROJECT_NAME}_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${${PROJECT_NAME}_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${${PROJECT_NAME}_VERSION_PATCH}")

include(CPack)
