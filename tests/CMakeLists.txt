### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008-2011 - Julien Wintz, Inria.
## Created: Mon Jun 20 18:01:59 2011 (+0200)
## Version: $Id$
## Last-Updated: Sun Sep 25 01:05:32 2011 (+0200)
##           By: Julien Wintz
##     Update #: 54
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
endif()

enable_testing()

add_test(dtkCompareDoubleTest ${CMAKE_BINARY_DIR}/bin/dtkCompareDouble)
add_test(dtkCompareFloatTest  ${CMAKE_BINARY_DIR}/bin/dtkCompareFloat)
add_test(dtkSmartPointerTest  ${CMAKE_BINARY_DIR}/bin/dtkSmartPointer)

if(ZLIB_FOUND)
add_test(dtkZipTest  ${CMAKE_BINARY_DIR}/bin/dtkZipTest ${CMAKE_BINARY_DIR}/tests/dtkZip)
endif(ZLIB_FOUND)

if(MSVC)
    set(PATH_STRING_FOR_TESTS "${QT_LIBRARY_DIR}")
else(MSVC)
    set(PATH_STRING_FOR_TESTS "$ENV{PATH}")
endif(MSVC)

string(REPLACE ";" "\\;" PATH_STRING_FOR_TESTS "${PATH_STRING_FOR_TESTS}")

set_tests_properties(dtkSmartPointerTest PROPERTIES ENVIRONMENT "PATH=${PATH_STRING_FOR_TESTS}")
