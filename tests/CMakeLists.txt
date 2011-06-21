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
add_subdirectory(dtkSmartPointer)
add_subdirectory(dtkZipZip)
add_subdirectory(dtkZipUnZip)
add_subdirectory(dtkZipChecksum)

enable_testing()

add_test(dtkCompareDoubleTest ${CMAKE_BINARY_DIR}/bin/dtkCompareDouble)
add_test(dtkCompareFloatTest  ${CMAKE_BINARY_DIR}/bin/dtkCompareFloat)
add_test(dtkSmartPointerTest  ${CMAKE_BINARY_DIR}/bin/dtkSmartPointer)
add_test(dtkZipZipTest        ${CMAKE_BINARY_DIR}/bin/dtkZipZip)
add_test(dtkZipUnzipTest      ${CMAKE_BINARY_DIR}/bin/dtkZipUnzip ${CMAKE_CURRENT_SOURCE_DIR}/dtkZipUnzip/archive.zip)
add_test(dtkZipChecksum       ${CMAKE_BINARY_DIR}/bin/dtkZipChecksum ${CMAKE_CURRENT_SOURCE_DIR}/dtkZipChecksum/archive.zip)
