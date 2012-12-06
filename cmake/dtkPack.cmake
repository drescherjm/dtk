### dtkPack.cmake --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Fri Apr  2 09:04:36 2010 (+0200)
## Version: $Id$
## Last-Updated: Thu Dec  6 12:57:36 2012 (+0100)
##           By: Julien Wintz
##     Update #: 55
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

include (InstallRequiredSystemLibraries)

## #################################################################
## Global settings
## #################################################################

set(CPACK_PACKAGE_NAME ${PROJECT_NAME})

if("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
  execute_process(COMMAND lsb_release -irs
    COMMAND sed "s/ //"
    COMMAND sed "s/Fedora/fc/"
    COMMAND tr -d '\n'
    OUTPUT_VARIABLE DISTRIB
    OUTPUT_STRIP_TRAILING_WHITESPACE)
  execute_process(COMMAND arch 
    OUTPUT_VARIABLE ARCH
    OUTPUT_STRIP_TRAILING_WHITESPACE)
  set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-${${PROJECT_NAME}_VERSION}-${DISTRIB}-${ARCH}")
else("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
  set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-${${PROJECT_NAME}_VERSION}.${CMAKE_SYSTEM_PROCESSOR}")
endif("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")

set(CPACK_SOURCE_PACKAGE_FILE_NAME "${PROJECT_NAME}-${${PROJECT_NAME}_VERSION}-src")

set(CPACK_PACKAGE_VENDOR "http://www.inria.fr/sophia/dream")
set(CPACK_PACKAGE_CONTACT "Julien Wintz <julien.wintz@inria.fr>")
set(CPACK_PACKAGE_DESCRIPTION_FILE ${CMAKE_CURRENT_SOURCE_DIR}/README.txt)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${PROJECT_NAME})
set(CPACK_PACKAGE_DESCRIPTION ${PROJECT_NAME})
set(CPACK_PACKAGE_VERSION_MAJOR ${${PROJECT_NAME}_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${${PROJECT_NAME}_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${${PROJECT_NAME}_VERSION_BUILD})
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/COPYING.txt)
set(CPACK_PACKAGING_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})

## #################################################################
## Generator list
## #################################################################

set(CPACK_BINARY_STGZ OFF)
set(CPACK_BINARY_TBZ2 OFF)
set(CPACK_BINARY_TGZ OFF)
set(CPACK_SOURCE_TBZ2 OFF)
set(CPACK_SOURCE_TGZ OFF)
set(CPACK_SOURCE_TZ OFF)
set(CPACK_SOURCE_ZIP OFF)

if(APPLE AND NOT UNIX)
  set(CPACK_GENERATOR "PackageMaker")
   set(CPACK_BUNDLE_NAME ${PROJECT_NAME})
endif(APPLE AND NOT UNIX)

if(WIN32)
  set(CPACK_GENERATOR "NSIS")
endif(WIN32)

if(UNIX AND NOT APPLE)
  set(CPACK_GENERATOR "DEB;RPM")
endif(UNIX AND NOT APPLE)

## #################################################################
## NSIS generator settings
## #################################################################

# ;

## #################################################################
## RPM generator settings
## #################################################################

# ;

## #################################################################
## DEB generator settings
## #################################################################

# ;

## #################################################################

include(CPack)
