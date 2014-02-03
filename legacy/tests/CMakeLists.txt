### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008-2011 - Julien Wintz, Inria.
## Created: Tue Jun 19 18:23:41 2012 (+0200)
## Version: $Id$
## Last-Updated: Thu Dec  6 12:56:28 2012 (+0100)
##           By: Julien Wintz
##     Update #: 9
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

configure_file(${CMAKE_SOURCE_DIR}/cmake/dtkSetTestEnvironment.cmake.in "${CMAKE_BINARY_DIR}/dtkSetTestEnvironment.cmake" @ONLY)

set_directory_properties(PROPERTIES TEST_INCLUDE_FILE "${CMAKE_BINARY_DIR}/dtkSetTestEnvironment.cmake")

add_subdirectory(dtkMath)
add_subdirectory(dtkCore)

if(DTK_BUILD_ZIP)
  add_subdirectory(dtkZip)
endif(DTK_BUILD_ZIP)
