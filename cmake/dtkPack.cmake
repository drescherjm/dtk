### dtkPack.cmake --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Fri Apr  2 09:04:36 2010 (+0200)
## Version: $Id$
## Last-Updated: Wed Apr 21 12:44:06 2010 (+0200)
##           By: Julien Wintz
##     Update #: 34
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
set(CPACK_PACKAGE_VENDOR "http://www.inria.fr/sophia/dream")
set(CPACK_PACKAGE_CONTACT "Julien Wintz <jwintz@sophia.inria.fr>")
set(CPACK_PACKAGE_DESCRIPTION_FILE ${CMAKE_CURRENT_SOURCE_DIR}/README.txt)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${PROJECT_NAME})
set(CPACK_PACKAGE_DESCRIPTION ${PROJECT_NAME})
set(CPACK_PACKAGE_VERSION_MAJOR ${${PROJECT_NAME}_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${${PROJECT_NAME}_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${${PROJECT_NAME}_VERSION_BUILD})
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/COPYING.txt)
set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-${${PROJECT_NAME}_VERSION}")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "${PROJECT_NAME}-${${PROJECT_NAME}_VERSION}-src")

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
endif(APPLE AND NOT UNIX)

if(WIN32)
  set(CPACK_GENERATOR "NSIS")
endif(WIN32)

if(UNIX AND NOT APPLE)
  set(CPACK_GENERATOR "RPM")
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

include(CPack)
