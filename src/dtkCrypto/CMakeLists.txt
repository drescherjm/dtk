### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Thu Jan  7 10:37:04 2010 (+0100)
## Version: $Id$
## Last-Updated: Thu Jan  7 19:27:54 2010 (+0100)
##           By: Julien Wintz
##     Update #: 14
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

project(dtkCrypto)

## #################################################################
## Resolve dependencies
## #################################################################

find_package(OpenSSL REQUIRED QUIET)

include_directories(${OPENSSL_INCLUDE_DIR})

## #################################################################
## Sources
## #################################################################

set(${PROJECT_NAME}_HEADERS
  dtkCryptoBase64.h
  dtkCryptoLicenseManager.h
)

set(${PROJECT_NAME}_HEADERS_MOC
)

set(${PROJECT_NAME}_SOURCES
  dtkCryptoBase64.c
  dtkCryptoLicenseManager.cpp
)

## #################################################################
## Build rules
## #################################################################

add_definitions(${QT_DEFINITIONS})
add_definitions(-DQT_SHARED)
add_definitions(-DQT_NO_DEBUG)

qt4_wrap_cpp(${PROJECT_NAME}_SOURCES_MOC ${${PROJECT_NAME}_HEADERS_MOC})

add_library(${PROJECT_NAME} SHARED
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_SOURCES_MOC}
  ${${PROJECT_NAME}_SOURCES_WRAP}
)

target_link_libraries(${PROJECT_NAME}
  ${QT_LIBRARIES}
  ${OPENSSL_LIBRARIES}
)

if(PYTHON_DEBUG_LIBRARIES)
  target_link_libraries(${PROJECT_NAME} debug ${PYTHON_DEBUG_LIBRARIES})
  target_link_libraries(${PROJECT_NAME} optimized ${PYTHON_LIBRARIES})
else(PYTHON_DEBUG_LIBRARIES)
  target_link_libraries(${PROJECT_NAME} ${PYTHON_LIBRARIES})
endif(PYTHON_DEBUG_LIBRARIES)

## #################################################################
## Installation
## #################################################################

if(NOT dtk_INSTALL_NO_DEVELOPMENT)
  install_files(${dtk_INSTALL_INCLUDE_DIR}/${PROJECT_NAME} .h ${${PROJECT_NAME}_HEADERS})
endif(NOT dtk_INSTALL_NO_DEVELOPMENT)

if(NOT dtk_INSTALL_NO_LIBRARIES)
  install_targets(${dtk_INSTALL_LIB_DIR} RUNTIME_DIRECTORY ${dtk_INSTALL_BIN_DIR} ${PROJECT_NAME})
endif(NOT dtk_INSTALL_NO_LIBRARIES)
