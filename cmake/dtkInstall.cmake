### dtkInstall.cmake --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Fri Apr  2 09:09:01 2010 (+0200)
## Version: $Id$
## Last-Updated: Fri Apr  2 09:09:23 2010 (+0200)
##           By: Julien Wintz
##     Update #: 2
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

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

if(NOT ${PROJECT_NAME}_INSTALL_MODULE_DIR)
  set(${PROJECT_NAME}_INSTALL_MODULE_DIR "/module")
endif(NOT ${PROJECT_NAME}_INSTALL_MODULE_DIR)

if(NOT ${PROJECT_NAME}_INSTALL_PACKAGE_DIR)
  set(${PROJECT_NAME}_INSTALL_PACKAGE_DIR "/cmake")
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
