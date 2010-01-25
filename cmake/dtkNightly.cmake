### dtkNightly.cmake --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Fri Jan  8 16:00:44 2010 (+0100)
## Version: $Id$
## Last-Updated: Mon Jan 25 09:54:25 2010 (+0100)
##           By: Julien Wintz
##     Update #: 5
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

# Set:
# PIPOL_IMAGE : Pipol image full name
# PIPOL_IMAGE_NAME : Pipol image without extension
# PIPOL_SITE : suggestion for SITE variable

set(PIPOL_IMAGE $ENV{PIPOL_IMAGE})  
set(_STMP "[${PIPOL_IMAGE}]")
if(_STMP STREQUAL "[]")
  set(PIPOL_IMAGE)
else(_STMP STREQUAL "[]")
  get_filename_component(PIPOL_IMAGE_NAME ${PIPOL_IMAGE} NAME_WE)
  set(PIPOL_SITE "PIPOL")
endif(_STMP STREQUAL "[]")

if(PIPOL_IMAGE)
  set(BUILDNAME "${PROJECT_NAME}-${CMAKE_GENERATOR}-${CMAKE_CXX_COMPILER}-${PIPOL_IMAGE_NAME}")
  set(SITE "${PIPOL_SITE}")
else(PIPOL_IMAGE)
  set(BUILDNAME "${PROJECT_NAME}-${CMAKE_GENERATOR}-${CMAKE_CXX_COMPILER}-${CMAKE_SYSTEM_NAME}")
endif(PIPOL_IMAGE)

if(PIPOL_IMAGE)
  set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-${${PROJECT_NAME}_VERSION}-${PIPOL_IMAGE_NAME}")
endif(PIPOL_IMAGE)
