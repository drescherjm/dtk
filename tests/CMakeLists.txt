### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008-2011 - Julien Wintz, Inria.
## Created: Mon Jun 20 18:01:59 2011 (+0200)
## Version: $Id$
## Last-Updated: Mon Jun 20 19:18:00 2011 (+0200)
##           By: Julien Wintz
##     Update #: 28
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

enable_testing()

add_test(dtkCompareDoubleTest ${CMAKE_BINARY_DIR}/bin/dtkCompareDouble)
add_test(dtkCompareFloatTest  ${CMAKE_BINARY_DIR}/bin/dtkCompareFloat)
add_test(dtkSmartPointerTest  ${CMAKE_BINARY_DIR}/bin/dtkSmartPointer)
