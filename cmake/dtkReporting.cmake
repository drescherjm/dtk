### dtkReporting.cmake --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008-2011 - Julien Wintz, Inria.
## Created: Mon Jun  6 14:49:42 2011 (+0200)
## Version: $Id$
## Last-Updated: Mon Jun  6 14:52:41 2011 (+0200)
##           By: Julien Wintz
##     Update #: 7
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################
if (EXISTS ${CMAKE_SOURCE_DIR}/cmake/${PROJECT_NAME}Dart.cmake.in)
#only create test variables if the project contains a proj_nameDart.cmake.in template file.
  set(DTK_CTEST_PROJECT_NAME ${PROJECT_NAME} CACHE STRING "Reporting project name.")
  set(DTK_CTEST_UPDATE_TYPE "git" CACHE STRING "Reporting update type.")
  set(DTK_CTEST_UPDATE_COMMAND "git" CACHE STRING "Reporting update command.")
  set(DTK_CTEST_DROP_METHOD "http" CACHE STRING "Reporting drop method.")
  set(DTK_CTEST_DROP_SITE "cdash.inria.fr" CACHE STRING "Reporting drop site.")
  set(DTK_CTEST_DROP_LOCATION "/CDash/submit.php?project=${PROJECT_NAME}" CACHE STRING "Reporting drop location.")
  set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_BINARY_DIR}/cmake")

  configure_file (
    "${CMAKE_SOURCE_DIR}/cmake/${PROJECT_NAME}Dart.cmake.in"
    "${CMAKE_BINARY_DIR}/cmake/${PROJECT_NAME}Dart.cmake")

  mark_as_advanced(BUILD_TESTING)
  mark_as_advanced(DART_TESTING_TIMEOUT)
  mark_as_advanced(DTK_CTEST_PROJECT_NAME)
  mark_as_advanced(DTK_CTEST_UPDATE_TYPE)
  mark_as_advanced(DTK_CTEST_UPDATE_COMMAND)
  mark_as_advanced(DTK_CTEST_DROP_METHOD)
  mark_as_advanced(DTK_CTEST_DROP_SITE)
  mark_as_advanced(DTK_CTEST_DROP_LOCATION)

  include(${PROJECT_NAME}Dart)
endif()
