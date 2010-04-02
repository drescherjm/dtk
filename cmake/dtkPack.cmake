### dtkPack.cmake --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Fri Apr  2 09:04:36 2010 (+0200)
## Version: $Id$
## Last-Updated: Fri Apr  2 12:24:44 2010 (+0200)
##           By: Julien Wintz
##     Update #: 22
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
## Global settings
## #################################################################

include(${CMAKE_ROOT}/Modules/InstallRequiredSystemLibraries.cmake)

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
set(CPACK_SOURCE_PACKAGE_FILE_NAME "${PROJECT_NAME}-${${PROJECT_NAME}_VERSION}")

## #################################################################
## Generator list
## #################################################################

set(CPACK_SOURCE_TBZ2 OFF)
set(CPACK_SOURCE_TGZ OFF)
set(CPACK_SOURCE_ZIP OFF)
set(CPACK_SOURCE_TZ OFF)

if(APPLE)
  set(CPACK_GENERATOR "PackageMaker")
endif(APPLE)

if(WIN32)
  set(CPACK_GENERATOR "NSIS")
endif(WIN32)

## #################################################################
## NSIS generator settings
## #################################################################

if(WIN32 AND NOT UNIX)
  set(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\\\${PROJECT_NAME}-${${PROJECT_NAME}_VERSION}.exe")
  set(CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_INSTALL_DIRECTORY}")
  set(CPACK_NSIS_HELP_LINK "http://www.inria.fr/sophia/dream/")
  set(CPACK_NSIS_URL_INFO_ABOUT "http://www.inria.fr/sophia/dream/")
  set(CPACK_NSIS_MODIFY_PATH ON)  
endif(WIN32 AND NOT UNIX)

## #################################################################
## DEB generator settings
## #################################################################

SET(CPACK_DEBIAN_PACKAGE_DEPENDS "swig")
SET(CPACK_DEBIAN_PACKAGE_SUGGESTS "dtk")

include(CPack)
