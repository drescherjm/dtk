### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008-2011 - Julien Wintz, Inria.
## Created: Mon Jun 20 18:01:59 2011 (+0200)
## Version: $Id$
## Last-Updated: Fri Sep 30 15:36:48 2011 (+0200)
##           By: Julien Wintz
##     Update #: 58
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

add_subdirectory(dtkCompareDouble)
add_subdirectory(dtkCompareFloat)
add_subdirectory(dtkSingleton)
add_subdirectory(dtkSmartPointer)
if(ZLIB_FOUND)
add_subdirectory(dtkZipTest)
endif(ZLIB_FOUND)

enable_testing()

add_test(NAME dtkCompareDoubleTest COMMAND $<TARGET_FILE:dtkCompareDouble>)
add_test(NAME dtkCompareFloatTest  COMMAND $<TARGET_FILE:dtkCompareFloat>)
add_test(NAME dtkSmartPointerTest  COMMAND $<TARGET_FILE:dtkSmartPointer>)

if(ZLIB_FOUND)
add_test(NAME dtkZipTest COMMAND $<TARGET_FILE:dtkZipTest> ${CMAKE_SOURCE_DIR}/tests/dtkZipTest)
endif(ZLIB_FOUND)
