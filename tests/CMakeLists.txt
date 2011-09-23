### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008-2011 - Julien Wintz, Inria.
## Created: Mon Jun 20 18:01:59 2011 (+0200)
## Version: $Id$
## Last-Updated: Fri Sep 23 10:43:06 2011 (+0200)
##           By: Julien Wintz
##     Update #: 49
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

enable_testing()

add_test(dtkCompareDoubleTest ${CMAKE_BINARY_DIR}/bin/dtkCompareDouble)
add_test(dtkCompareFloatTest  ${CMAKE_BINARY_DIR}/bin/dtkCompareFloat)
add_test(dtkSmartPointerTest  ${CMAKE_BINARY_DIR}/bin/dtkSmartPointer)

if(MSVC)
    set(PATH_STRING_FOR_TESTS "${QT_LIBRARY_DIR}")
else(MSVC)
    set(PATH_STRING_FOR_TESTS "$ENV{PATH}")
endif(MSVC)

string(REPLACE ";" "\\;" PATH_STRING_FOR_TESTS "${PATH_STRING_FOR_TESTS}")

set_tests_properties(dtkSmartPointerTest PROPERTIES ENVIRONMENT "PATH=${PATH_STRING_FOR_TESTS}")
