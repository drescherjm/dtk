### dtkReporting.cmake --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008-2011 - Julien Wintz, Inria.
## Created: Mon Jun  6 14:49:42 2011 (+0200)
## Version: $Id$
## Last-Updated: Thu Jun 30 22:25:09 2011 (+0200)
##           By: Julien Wintz
##     Update #: 31
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

  find_program(HOSTNAME_CMD NAMES hostname)
  exec_program(${HOSTNAME_CMD} ARGS "-s" OUTPUT_VARIABLE HOSTNAME)

  find_program(UNAME NAMES uname)

  macro(getuname name flag)
    exec_program("${UNAME}" ARGS "${flag}" OUTPUT_VARIABLE "${name}")
  endmacro(getuname)

  getuname(osname -s)
  getuname(osrel -r)
  getuname(cpu -m)

  set(DTK_CTEST_BUILD_NAME "${osname}-${osrel}-${cpu}" CACHE STRING "Reporting build name.")
  set(DTK_CTEST_SITE "${HOSTNAME}" CACHE STRING "Reporting site name.")
  set(DTK_CTEST_PROJECT_NAME ${PROJECT_NAME} CACHE STRING "Reporting project name.")
  set(DTK_CTEST_UPDATE_TYPE "git" CACHE STRING "Reporting update type.")
  set(DTK_CTEST_UPDATE_COMMAND "git" CACHE STRING "Reporting update command.")
  set(DTK_CTEST_DROP_METHOD "http" CACHE STRING "Reporting drop method.")
  set(DTK_CTEST_DROP_SITE "dtk.inria.fr" CACHE STRING "Reporting drop site.")
  set(DTK_CTEST_DROP_LOCATION "/dashboard/submit.php?project=${PROJECT_NAME}" CACHE STRING "Reporting drop location.")
  set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_BINARY_DIR}/cmake")

  configure_file (
    "${CMAKE_SOURCE_DIR}/cmake/${PROJECT_NAME}Dart.cmake.in"
    "${CMAKE_BINARY_DIR}/cmake/${PROJECT_NAME}Dart.cmake")

  mark_as_advanced(DART_TESTING_TIMEOUT)
  mark_as_advanced(HOSTNAME_CMD)
  mark_as_advanced(UNAME)
  mark_as_advanced(DTK_CTEST_BUILD_NAME)
  mark_as_advanced(DTK_CTEST_SITE)
  mark_as_advanced(DTK_CTEST_PROJECT_NAME)
  mark_as_advanced(DTK_CTEST_UPDATE_TYPE)
  mark_as_advanced(DTK_CTEST_UPDATE_COMMAND)
  mark_as_advanced(DTK_CTEST_DROP_METHOD)
  mark_as_advanced(DTK_CTEST_DROP_SITE)
  mark_as_advanced(DTK_CTEST_DROP_LOCATION)

  include(${PROJECT_NAME}Dart)
endif()
