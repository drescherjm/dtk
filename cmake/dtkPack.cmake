### dtkPack.cmake --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Fri Apr  2 09:04:36 2010 (+0200)
## Version: $Id$
## Last-Updated: Wed Sep 22 16:39:32 2010 (+0200)
##           By: Julien Wintz
##     Update #: 45
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
  #GET distribution id
  execute_process(COMMAND lsb_release -irs
    COMMAND sed "s/ //"
    COMMAND sed "s/Fedora/fc/"
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
set(CPACK_PACKAGE_CONTACT "Julien Wintz <jwintz@sophia.inria.fr>")
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

set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.4), libgcc1 (>= 1:4.1.1), libpython2.6 (>= 2.6), libqt4-help (>= 4:4.5.3), libqt4-network (>= 4:4.5.3), libqt4-opengl (>= 4:4.5.3), libqt4-sql (>= 4:4.5.3), libqt4-webkit (>= 4:4.5.3), libqt4-xml (>= 4:4.5.3), libqt4-xmlpatterns (>= 4:4.5.3), libqtcore4 (>= 4:4.6.1), libqtgui4 (>= 4:4.6.1), libssl0.9.8 (>= 0.9.8k-1), libstdc++6 (>= 4.4.0), tcl8.4 (>= 8.4.16)")

include(CPack)
