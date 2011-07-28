### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008-2011 - Julien Wintz, Inria.
## Created: Mon Jun 20 18:01:59 2011 (+0200)
## Version: $Id$
## Last-Updated: Tue Jun 21 16:09:15 2011 (+0200)
##           By: Julien Wintz
##     Update #: 44
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
    add_subdirectory(dtkZipZip)
    add_subdirectory(dtkZipUnzip)
    add_subdirectory(dtkZipChecksum)
endif(ZLIB_FOUND)

enable_testing()

add_test(dtkCompareDoubleTest ${CMAKE_BINARY_DIR}/bin/dtkCompareDouble)
add_test(dtkCompareFloatTest  ${CMAKE_BINARY_DIR}/bin/dtkCompareFloat)
add_test(dtkSmartPointerTest  ${CMAKE_BINARY_DIR}/bin/dtkSmartPointer)
if(ZLIB_FOUND)
    add_test(dtkZipZipTest        ${CMAKE_BINARY_DIR}/bin/dtkZipZip)
    add_test(dtkZipUnzipTest      ${CMAKE_BINARY_DIR}/bin/dtkZipUnzip ${CMAKE_CURRENT_SOURCE_DIR}/dtkZipUnzip/archive.zip)
    add_test(dtkZipChecksum       ${CMAKE_BINARY_DIR}/bin/dtkZipChecksum ${CMAKE_CURRENT_SOURCE_DIR}/dtkZipChecksum/archive.zip)
endif(ZLIB_FOUND)

if(MSVC)
    #May need to add zlib path?
    set(PATH_STRING_FOR_TESTS "${QT_LIBRARY_DIR}")
else(MSVC)
    set(PATH_STRING_FOR_TESTS "$ENV{PATH}")
endif(MSVC)

# ';' deliminates stringlists in CMake, but here we want to preserve them.)
string(REPLACE ";" "\\;" PATH_STRING_FOR_TESTS "${PATH_STRING_FOR_TESTS}")

set_tests_properties(dtkSmartPointerTest PROPERTIES ENVIRONMENT "PATH=${PATH_STRING_FOR_TESTS}")
if(ZLIB_FOUND)
    set_tests_properties(dtkZipZipTest PROPERTIES ENVIRONMENT "PATH=${PATH_STRING_FOR_TESTS}")
    set_tests_properties(dtkZipUnzipTest PROPERTIES ENVIRONMENT "PATH=${PATH_STRING_FOR_TESTS}")
    set_tests_properties(dtkZipChecksum PROPERTIES ENVIRONMENT "PATH=${PATH_STRING_FOR_TESTS}")
endif(ZLIB_FOUND)
