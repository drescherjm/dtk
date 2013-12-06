### dtkPack.cmake --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Fri Apr  2 09:04:36 2010 (+0200)
## Version: $Id$
## Last-Updated: ven. déc.  6 09:23:33 2013 (+0100)
##           By: Nicolas Niclausse
##     Update #: 151
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

#set(CPACK_COMPONENTS_ALL apps devel libs)

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

  set(CPACK_PACKAGING_INSTALL_PREFIX  "usr" CACHE PATH "Where you want to install your package")
  mark_as_advanced(CPACK_PACKAGING_INSTALL_PREFIX)

else("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
  set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-${${PROJECT_NAME}_VERSION}.${CMAKE_SYSTEM_PROCESSOR}")
  set(CPACK_PACKAGING_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})
endif("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")

set(CPACK_SOURCE_PACKAGE_FILE_NAME "${PROJECT_NAME}-${${PROJECT_NAME}_VERSION}-src")

set(CPACK_PACKAGE_VENDOR "INRIA")
set(CPACK_PACKAGE_CONTACT "Julien Wintz <julien.wintz@inria.fr>")
set(CPACK_PACKAGE_DESCRIPTION_FILE ${CMAKE_CURRENT_SOURCE_DIR}/README.txt)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${PROJECT_NAME})
set(CPACK_PACKAGE_VERSION_MAJOR ${${PROJECT_NAME}_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${${PROJECT_NAME}_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${${PROJECT_NAME}_VERSION_BUILD})
#set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/COPYING.txt)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING.txt")

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


## #############################################################################
## Add postinst and prerm script
## #############################################################################

if(UNIX AND NOT APPLE)
  if(${DISTRIB} MATCHES fc|fedora|Fedora|Centos|centos|SUSE|Suse|suse)
    ## #################################################################
    ## RPM generator settings
    ## #################################################################

    set(CPACK_GENERATOR "RPM")

    set(CPACK_RPM_PACKAGE_REQUIRES "qt")

    if(DTK_HAVE_MPI AND DTK_BUILD_DISTRIBUTED)
      set(CPACK_RPM_PACKAGE_REQUIRES ${CPACK_RPM_PACKAGE_REQUIRES} " openmpi")
    endif(DTK_HAVE_MPI AND DTK_BUILD_DISTRIBUTED)

    if(DTK_HAVE_FFMPEG AND DTK_BUILD_VIDEO)
      set(CPACK_RPM_PACKAGE_REQUIRES ${CPACK_RPM_PACKAGE_REQUIRES} " ffmpeg-libs")
    endif(DTK_HAVE_FFMPEG AND DTK_BUILD_VIDEO)

    if(DTK_HAVE_PLOT AND DTK_BUILD_PLOT)
      set(CPACK_RPM_PACKAGE_REQUIRES ${CPACK_RPM_PACKAGE_REQUIRES} " qwt")
    endif(DTK_HAVE_PLOT AND DTK_BUILD_PLOT)

    message(STATUS "RPM REQUIRES: " ${CPACK_RPM_PACKAGE_REQUIRES})

    set(CPACK_RPM_PACKAGE_LICENSE "BSD")
    set(CPACK_RPM_PACKAGE_GROUP "System Environment/Libraries")
    set(CPACK_INSTALL_STUFF  ${CMAKE_BINARY_DIR})
    # set(CPACK_RPM_COMPONENT_INSTALL ON)
    # set(CPACK_COMPONENTS_ALL apps devel libs)

  else()
    ## #################################################################
    ## DEB generator settings
    ## #################################################################

    set(CPACK_GENERATOR "DEB")
  endif()
endif(UNIX AND NOT APPLE)


## #################################################################
## NSIS generator settings
## #################################################################

## #################################################################

include(CPack)
